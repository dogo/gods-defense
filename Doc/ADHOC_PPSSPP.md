# Testar o multiplayer adhoc no PPSSPP

Como rodar duas instâncias do PPSSPP no mesmo Mac e fazê-las se encontrar em
modo adhoc, por meio de um relay local (aemu_postoffice). **Não precisa de
sudo:** o relay escuta no IP da rede local do Mac. Validado assim com o
PPSSPP SDL 1.20.4 no macOS em 2026-11-02.

```
 PPSSPP host  ──┐                       ┌── PPSSPP cliente
 MAC 4c:2f:…    ├──► relay (aemu) ◄─────┤   MAC 02:11:22:33:44:55
 nick PPSSPP    │   <IP>:27312 controle │   nick PEER
                │   <IP>:27313 dados    │
```

## Antes de começar: o que costuma quebrar

| Sintoma | Causa | Solução |
|---|---|---|
| `oslAdhocInit` nunca retorna; estado de controle fica em 0 | A OSLib até 1.5.3 envia o product ID com 8 caracteres (`ULUS9999`) e o servidor recusa | Instalar a OSLib com o fix (branch `fix/adhoc-hardening`); o jogo não tem mais workaround |
| As duas instâncias ficam com o mesmo IP (127.0.0.1) e o mesmo MAC | Bug do contador de instâncias do PPSSPP no macOS (`ftruncate` em shm já existente dá `EINVAL`). Corrigido em hrydgard/ppsspp#22895, que não está no 1.20.4 | Abrir o cliente com `--appendconfig` com outro MAC e outro nickname |
| `sceNetAdhocctlConnect` falha com `80410b10` depois de ~5 s e o relay não registra conexão | O PPSSPP não se conecta quando o IP do servidor é o mesmo da instância (127.0.0.1) e o servidor embutido está desligado | Rodar o relay no IP da rede local do Mac (seção 1) |
| Conecta, mas usa P2P em vez do relay | Servidor fora de `RelayAdhocServerList` | Colocar o IP também em `RelayAdhocServerList` |
| Sessões de dados expiram | `strict_mode` do relay exige o mesmo IP de origem no controle e nos dados | `strict_mode: false` |
| Ao reabrir, o host está com o MAC/nick do cliente | O cliente grava a config de `--appendconfig` no `ppsspp.ini` principal, mesmo quando é encerrado com `kill -9` | Restaurar `NickName`/`MacAddress` antes de abrir o host (o script abaixo já faz isso) |
| O pedido do cliente nunca chega ao host | A OSLib ignora o pedido (`MATCHING_SELECTED`) de um PSP do qual o host ainda não recebeu HELLO, e em P2P o cliente para de mandar HELLO depois do pedido | O lobby só permite escolher o host 4 s depois de ele aparecer (o HELLO sai a cada 3 s) |
| `oslAdhocRequestConnection` retorna -1 na hora | OSLib até 1.5.3: `time_t` de 64 bits contra o `sceKernelLibcTime` de 32 bits | OSLib com o fix (`fix/adhoc-hardening`). O jogo não usa essa função |

## 1. Compilar o relay (uma vez só)

```sh
git clone https://github.com/Kethen/aemu_postoffice.git /tmp/aemu
cd /tmp/aemu/server_cpp
bash build_linux.sh          # também funciona no macOS
```

Em `server_cpp/config.json`, mudar:

```json
"ip_addr": "::FFFF:192.168.15.4",
"strict_mode": false,
"http_status_server_port": 18888
```

- `ip_addr` é o IP de escuta: o IP do Mac na rede local, que pode ser consultado com `ipconfig getifaddr en0` (ou `en1`). Use esse mesmo IP no lugar de `192.168.15.4` em todo este guia.
- `http_status_server_port` precisa ser uma porta válida e livre, porque o relay rejeita `0`.

O relay lê `config.json` e `game_db.json` do diretório atual, então rode a
partir de `server_cpp`:

```sh
cd /tmp/aemu/server_cpp && ./aemu_postoffice
lsof -nP -iTCP:27312 -iTCP:27313 -sTCP:LISTEN   # deve mostrar as duas portas
```

Enquanto o relay estiver rodando, ele fica acessível pela rede local. Se o
Mac trocar de rede (e de IP), atualize `ip_addr` e o `ppsspp.ini`.

> Por que não 127.0.0.1: as duas instâncias usam esse IP, e o PPSSPP se recusa a
> conectar num servidor que tem o IP da própria instância. A alternativa sem rede
> é um alias de loopback, que exige sudo (`sudo ifconfig lo0 alias 127.0.0.2 up`,
> e depois `-alias` para remover), com `ip_addr` `::FFFF:127.0.0.2`.

## 2. Configurar o PPSSPP

A config fica em `~/.config/ppsspp/PSP/SYSTEM/ppsspp.ini` e é compartilhada
pelas duas instâncias. **Faça backup antes de editar:**

```sh
cp ~/.config/ppsspp/PSP/SYSTEM/ppsspp.ini ~/ppsspp.ini.backup
```

Com o PPSSPP fechado, editar em `[Network]`:

```ini
EnableWlan = True
EnableAdhocServer = False
proAdhocServer = 192.168.15.4
RelayAdhocServerList = 192.168.15.4
AdhocServerRelayMode = 0
```

Arquivo de configuração extra do cliente, por exemplo `~/ppsspp-peer.ini`:

```ini
[SystemParam]
NickName = PEER
MacAddress = 02:11:22:33:44:55
```

## 3. Abrir as duas instâncias

Abra o host primeiro e o cliente alguns segundos depois, usando o executável
direto (sem `open`), para cada instância ter o próprio log:

```sh
PPSSPP=/Applications/PPSSPPSDL.app/Contents/MacOS/PPSSPPSDL
EBOOT="$PWD/PSP Project/EBOOT.PBP"

# o cliente anterior deixou o MAC/nick dele no ini; devolve a identidade do host
sed -i '' -e 's/^NickName = .*/NickName = PPSSPP/' \
          -e 's/^MacAddress = .*/MacAddress = 4c:2f:52:b0:8a:ce/' \
          ~/.config/ppsspp/PSP/SYSTEM/ppsspp.ini

$PPSSPP --windowed --log=/tmp/ppsspp-host.log "$EBOOT" &
sleep 4
$PPSSPP --windowed --appendconfig=$HOME/ppsspp-peer.ini --log=/tmp/ppsspp-client.log "$EBOOT" &
```

Troque os valores de `NickName`/`MacAddress` do host pelos seus, que estão no
backup do ini.

Os arquivos que o jogo abre com caminho relativo (por exemplo, logs de teste)
vão para a pasta do `EBOOT.PBP`, porque o PPSSPP a monta como `umd0:/`.

## 4. No jogo

1. Nas duas janelas, entre em **Multiplayer**.
2. No host, aperte **Cross** ("servidor"). No cliente, aperte **Square** ("cliente").
3. Escolha o mapa nas opções de jogo. O mapa do host prevalece, e o cliente carrega o mapa do host se o hash do XML for igual.
4. No lobby do cliente, o host aparece como "getting ready" por 4 segundos antes de poder ser selecionado (veja a tabela acima).
5. Aceite o pedido no host com Cross.

Com `PauseOnLostFocus = False` (já configurado), a janela que perde o foco
continua rodando. Não use savestates nem speed hack durante uma partida em rede.

## 5. Ler os logs

```sh
grep -E "Relay server mode|FriendFinder|Matching Event|sceNetAdhocctl -" /tmp/ppsspp-host.log
```

| Linha | O que indica |
|---|---|
| `server X is in custom list with relay, using data mode AdhocDataMode::AemuPostoffice` | Modo relay ativo |
| `FriendFinder: Incoming OPCODE_CONNECT [mac][…][nick]` | O servidor anunciou o outro PSP |
| `Result (00000000) of sceNetAdhocctl - Event: 1, State: 1` | Controle conectado. `oslAdhocInit` deve continuar a partir daqui |
| `Result (80410b10) … Opcode: 2` | Não conseguiu falar com o servidor (veja a tabela acima) |
| `Matching Event [1=HELLO]` / `[2=JOIN]` / `[6=ACCEPT]` / `[7=ESTABLISHED]` / `[10=…]` | Eventos de matching. Na OSLib, eles são `MATCHING_JOINED`, `MATCHING_SELECTED`, `MATCHING_ACCEPTED`, `MATCHING_ESTABLISHED` e `MATCHING_DISCONNECT` |

## 6. Terminar

```sh
pkill -f aemu_postoffice
cp ~/ppsspp.ini.backup ~/.config/ppsspp/PSP/SYSTEM/ppsspp.ini   # PPSSPP fechado
```

Restaurar o ini devolve o MAC original, o que importa para os saves de outros
jogos, e desliga a WLAN.
