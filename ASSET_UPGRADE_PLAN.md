# Plano de Evolucao Visual - Gods Defense

> Base validada contra o codigo, o git e o kit em 2026-10-18; menu principal atualizado em 2026-11-02.
> Legenda: **[feito]** verificado no repo · **[parcial]** · **[pendente]** · **[fora do escopo]**
> Referencia do kit: `ASSET_MAP.md`.

## Objetivo

Atualizar o visual do jogo usando o pacote `tower-defense-2d-game-kit-v1.1`, mantendo o tema mitologico/fantasia de `Gods Defense`, mas deixando a apresentacao mais profissional, animada e consistente no PSP.

A direcao geral deve ser: fantasia cartunesca, clara, com leitura boa em tela pequena, sem perder a identidade de deuses, monstros e defesa de templo.

## Assets protegidos (nao alterar)

- `PSP Project/Res/background.png` (`IMG_MAIN_MENU_BG`, fundo do `MainMenuScreen`): o menu principal novo deve ser feito **por cima** dele
- `PSP Project/Res/GDSplash.png` (Title Screen)
- `PSP Project/Res/anykeylogo.png` (Anykey Screen)

Os tres nao mudam desde `337b99b` (otimizacao pngout antiga).

## 0. Pipeline de assets (fonte da verdade)

Todo PNG de gameplay/HUD/menu trocado ate agora e gerado por script. **Nao editar esses PNGs a mao.** Altere o script e rode de novo.

- Rodar com `.venv/bin/python tools/asset_pipeline/<script>.py`. O script escreve direto em `PSP Project/Res/`.
- O kit (`tower-defense-2d-game-kit-v1.1/`) esta no `.gitignore`, entao precisa existir localmente.
- **Reprodutibilidade verificada:** os 33 PNGs abaixo foram apagados e regenerados numa copia isolada, e sairam pixel a pixel identicos aos commitados.

| Script | Saidas | Fonte no kit |
|---|---|---|
| `build_arrow_tower.py` | `towers/arrow/{tower,icon,ST_Arrow}.png` | archer `6.png` (torre), `35.png` (flecha); `td-gui/upgrade/ico_8` |
| `build_fire_tower.py` | `towers/fire/{tower,icon,ST_Fire}.png` | magic `4.png`, `14.png`; `td-gui/interface_game/ico_1` |
| `build_ice_tower.py` | `towers/ice/{tower,icon,ST_Ice}.png` | magic `8.png`, `10.png`; `td-gui/upgrade/ico_21` |
| `build_lightning_tower.py` | `towers/lightning/{tower,icon,ST_Lightning}.png` | magic `18.png`, `19/20.png`; `td-gui/upgrade/ico_18` |
| `build_<inimigo>_enemy.py` (7) + `enemy_assets.py` | `enemies/*/*.png` | ver tabela da secao 2 |
| `build_ingame_ui.py` | `hud`, `sidebar`, `upgradebar`, `selector`, `sell`, `upgrade` `.png` | `td-gui/PNG/*` (crystal_1 do `shop`, heart do `interface_game`) |
| `build_main_menu.py` | `menu/buttons.png` (2 estados de `192x28`) | `td-gui/difficulty/button_empty_2` |
| `build_maps.py` | `maps/*/{<mapa>.png, mini.png}` + `_debug/*` | `td-tilesets/version-for-the-program-Tiled` |
| `preview_tiles.py` | `_debug/{tail}_sheet.png` (as 8 familias) | idem |

O antigo `tools/import_kit_enemies.py` (legado, com outro mapeamento de monstros) foi removido.

## 1. Torres — [parcial]

### Objetivo visual

As torres precisam parecer mais fortes, distintas entre si e legiveis em `32x32`. Cada torre deve comunicar sua funcao sem depender de texto.

### Mapeamento aplicado

| Torre | Asset atual |
|---|---|
| Arrow Tower | archer tower (`archer-tower-game-assets/PNG/6.png`) |
| Fire Tower | magic tower (`magic-tower-game-assets/PNG/4.png`) |
| Ice Tower | magic tower (`magic-tower-game-assets/PNG/8.png`) |
| Lightning Tower | magic tower (`magic-tower-game-assets/PNG/18.png`) |

`stone-tower-game-assets` e `support-tower-game-assets` nao sao usados.

### Status

- [feito] `tower.png`, `icon.png` e `ST_*.png` novos para as 4 torres (sheets `128x32`, 4 frames de `32x32`).
- [feito] Projeteis novos: flecha e cristal com tremida de ±1px, bola de fogo pulsando em tamanho (12→16px), raio alternando os frames 19/20.
- [feito] **Idle das torres magicas:** `accent_idle_frames()` (em `build_arrow_tower.py`) faz pulsar so os pixels de destaque saturados, com brilho 1.0 → 1.25 → 1.5 → 1.25 em ping-pong:
  - fogo: gemas amarelas/vermelhas
  - gelo: faixas turquesa
  - eletrica: pontos vermelhos
- [pendente] **Arrow Tower** continua estatica de proposito: a base de madeira/palha nao tem detalhe luminoso. Um idle real precisaria de arte nova (arqueiro/bandeira).

### Entregaveis restantes

- Idle da Arrow Tower (precisa de arte).
- Revisar no emulador se o `FrameTime` atual (95–150 ms) deixa o pulso agradavel.

## 2. Inimigos — [parcial]

### Objetivo visual

Os inimigos devem parecer parte de um exercito mitologico/fantasia, com silhuetas diferentes e movimento mais vivo.

### Mapeamento aplicado

Todos sao sheets `384x32` com 12 frames `32x32` (`Frames="12"` no `enemy.xml`).

| Inimigo | Pack / monstro | Animacao | Frames unicos no sheet |
|---|---|---|---:|
| Minions | `2d-monster-sprites/1` | `run` | 12 |
| Cyclops | `2d-monster-sprites/3` | `run` | 12 |
| Medusa | `2d-monster-sprites/7` | `run` | 12 |
| Cerberus | `monster-enemy-game-sprites/9` | `run` | 12 |
| Minotaur | `tower-defense-monster-2d-sprites/7` | `RUN` | 6 |
| Griffin (voador) | `tower-defense-monster-2d-sprites/10` | `WALK` | 6 |
| Hydra | `monster-character-2d-sprites/3` | `RUN` | 10 |

Minotaur e griffin tem so 6 frames unicos porque o proprio kit repete frames (ver ASSET_MAP > Frames duplicados).

### Status

- [feito] Spritesheets novos para os 7 inimigos.
- [feito] Polimento no engine (`7329bdc`, codigo, nao sprite):
  - sprite em pe, espelhado quando anda para a esquerda
  - flash vermelho ao levar dano
  - tinta azul e ciclo mais lento quando em slow
  - fade-out na morte (estado `ENEMY_DYING`)
  - frame inicial aleatorio
  - voadores flutuando
- [feito] **Loop sem salto:** `enemy_assets.frame_paths()` agora amostra o ciclo inteiro de 20 frames em intervalos iguais. Antes pegava `000`–`011` e a emenda `011→000` era 2,5–4× um passo normal. Agora fica em 1,1–1,5× (a Medusa tem 1,55× porque o proprio kit ja salta entre `019` e `000`).
- [verificar] Com o ciclo completo em 12 frames, as pernas de Cerberus, Medusa, Minions e Cyclops se movem ~1,67× mais rapido com o mesmo `FrameTime`. Conferir no emulador se o passo nao parece "patinando"; se parecer, aumentar o `FrameTime` no `enemy.xml`.
- [pendente] Barra de vida: continua sendo dois retangulos (vermelho + verde) de `32x4` sem borda, em `EnemyRenderer::RenderEnemyHealthBar`. Proposta:
  - barra menor e mais polida
  - borda escura
  - cor muda conforme vida baixa
- [pendente] Sprites de `hurt`/`die`. O kit tem, mas hoje o feedback e so tinta/fade por codigo.
- [nao aplicado] "Rapidos usam `run`, pesados usam `walk`": hoje todos usam `run`/`RUN`, menos o griffin (`WALK`).

## 3. UI Ingame / HUD — [parcial]

### Objetivo visual

A UI ingame deve parecer menos prototipo e mais jogo final, mas sem ocupar espaco demais na tela `480x272`.

### Status

- [feito] `hud.png` com icone de cristal (ouro) e coracao (vida); `sidebar.png`, `upgradebar.png`, `selector.png`, `sell.png` e `upgrade.png` redesenhados (`bc2b1e8`).
- [feito] `GameGUI.cpp`: fonte do HUD reduzida para `0.50` e posicoes de texto/custo ajustadas.
- [pendente] `cursor.png` nao mudou.
- [pendente] Range circle: continua `Drawing::drawCircle` vermelho, igual para preview e torre selecionada.
- [pendente] Nao ha feedback de "nao pode construir". O preview (`GameGUI::RenderPlacingTower`) e sempre o mesmo, e a falta de ouro abre um `oslMessageBox`.
- [pendente] Animacoes:
  - selector piscando
  - icone de torre com destaque quando selecionado
  - botao de start wave animado
- `Resource.h` nao precisou de mudanca: os nomes dos arquivos foram mantidos.

## 4. Menus — [parcial]

### Objetivo visual

Os menus devem passar uma primeira impressao mais profissional, com um estilo visual unico entre as telas.

**Main Menu implementado:** seis botoes de madeira com moldura metalica, selecao dourada pulsante e rotulos com tamanho uniforme. O fundo protegido e as seis acoes existentes foram mantidos. `build_main_menu.py` gera um sheet RGBA `384x28`, carregado e liberado pelo `MainMenuScreen`.

Os botoes sao desenhados antes dos textos: intraFont altera a textura GU sem atualizar o cache de imagem da OSLib, causando artefatos quando se alterna o mesmo sheet com texto.

As demais telas ainda nao receberam o upgrade visual. A pasta `PSP Project/Res/mapselect/` e sobra local sem referencia no codigo.

Validado em 2026-11-02: build PSP, regeneracao deterministica do sheet, assets protegidos identicos ao HEAD e PPSSPP (layout, navegacao circular, entrada na selecao de mapa e retorno ao menu). PSP real e medicao de memoria ainda pendentes.

### Restricoes ja decididas

- Title, Anykey e o fundo do menu principal sao protegidos (ver topo). Nao criar novo background principal nem novo logo; botoes e molduras novos entram por cima.
- `td-gui/PNG/win` e `td-gui/PNG/failed` **nao** devem ser usados por enquanto: nao combinam com a identidade do jogo.
- `EndingScreen` (vitoria/derrota) esta **[fora do escopo]** ate a direcao visual ser definida. Nao existem `ending_win.png`/`ending_failed.png` no repo, nem no historico do git.

### Assets candidatos

- `td-gui/PNG/menu`, `levels`, `settings`, `difficulty`, `load_bar` (botoes, molduras, cordas, setas)

### Telas existentes (`PSP Project/Src/*Screen.cpp`)

| Tela | Classe | Status |
|---|---|---|
| Title | `TitleScreen` | manter (`GDSplash.png`) |
| Anykey | `AnykeyScreen` | manter (`anykeylogo.png`) |
| Warning | `WarningScreen` | pendente |
| Memory Warning | `MemoryWarningScreen` | pendente |
| Main Menu | `MainMenuScreen` | feito — botoes e selecao pulsante (fundo `background.png` mantido) |
| Selecao de mapa | `GameOptionsScreen` (carrega `maps/%s/mini.png`) | pendente |
| Pause | `PauseScreen` | pendente |
| Help | `HelpScreen` | pendente |
| About | `AboutScreen` | pendente |
| Trophies | `TrophiesScreen` | pendente |
| Multiplayer | `MultiplayerScreen` | pendente |
| Exit Confirmation | `ExitScreen` | pendente |
| Win/Ending | `EndingScreen` | fora do escopo |

### Melhorias propostas

- Substituir botoes de texto puro por botoes visuais (`td-gui/menu`).
- Linguagem visual consistente:
  - madeira/pedra/metal
  - brilho dourado
  - icones claros
- Transicoes simples:
  - fade in/fade out
  - botao selecionado pulsando
  - seta/selector animado
- Selecao de mapa: melhorar o card/preview, destacando nome, descricao e miniatura.

### Entregaveis

- [feito] `tools/asset_pipeline/build_main_menu.py` e integracao no `MainMenuScreen`.
- [pendente] Aplicar a linguagem visual em `PauseScreen` e `GameOptionsScreen`, depois nas demais telas.
- [pendente] Transicoes de entrada/saida e validacao em PSP real.

## 5. Mapas e Ambiente — [parcial]

### Objetivo visual

Os mapas precisam continuar legiveis para tower defense, mas podem ganhar acabamento melhor e mais vida.

### Formato atual

- `maps/<nome>/<nome>.png`: `480x480` (grid 15x15 de celulas `32x32`; `MapImg Width="15" Height="15"`)
- `maps/<nome>/mini.png`: `100x100`
- `maps/<nome>/map.xml`: `CollisionMap`, `Path`, waves. Nao foi alterado pela pipeline; o unico commit nele desde entao foi normalizacao de fim de linha.

### Status

- [feito] Os 4 mapas existentes (`olympus`, `icarusfalls`, `rescueathena`, `icymanipulator`) foram re-renderizados por `build_maps.py` (`f768806`), com tiles de `version-for-the-program-Tiled`.
- [feito] **Map Composer semantico.** O que antes era a "proxima direcao" ja esta implementado:
  - le o `map.xml`, rasteriza o `<Path>` e classifica cada celula em `path`, `path_margin`, `corner`, `edge`, `pocket`, `dead_zone` ou `buildable_core`
  - perfil de bioma por mapa (`BIOME_PROFILES`)
  - props so em `corner`/`edge`/`dead_zone`/`pocket`
  - render em hi-res (256px/celula) com downscale LANCZOS para 480
  - estrada como tracado continuo pelos checkpoints, com textura feita do miolo do tile de estrada
  - debug em `_debug/<mapa>_classes_{overlay,solid}.png` e `_debug/<mapa>_plan.png` (este com legenda: contagem de zonas, de props por categoria e de erros)
- [parcial] **Validacao:** `validate_placements()` detecta props em classe proibida, imprime `! ...` e o prop e **descartado**, mas o script nao falha (exit 0). Hoje os 4 mapas dao `errors=0`.
- [pendente] Folha unica de preview dos 4 mapas.
- [pendente] Manifest em arquivo. Hoje as contagens so saem no stdout e na legenda do `_plan.png`.
- [pendente] Mapa novo. Ate agora so houve re-render dos 4 existentes.
- [pendente] Atualizar o MapGenerator (`tools/MapGenerator`).

### Perfis de bioma em uso (verificado)

Tiles que o planner realmente coloca hoje. Todos sao props isolados, conforme ASSET_MAP:

| Mapa | Familia | Base | Props colocados |
|---|---|---:|---|
| `olympus` | `tail_2` areia/ruinas | `21` | `43` torre de vigia (4) |
| `icarusfalls` | `tail_7` pantano/cemiterio | `26` | `35`/`36` arvore morta (4), `33` lapides (6), `24` cabana (1) |
| `rescueathena` | `tail_1` grama/vila | `42` | `33` arvore (4), `28` casa (2) |
| `icymanipulator` | `tail_4` neve | `35` | `21` torre (4), `29` pinheiro (6), `31` cabana (2) |

### Regras de composicao (fonte unica)

- Area construivel central (`buildable_core`) nao recebe props opacos: eles parecem obstaculo e atrapalham a leitura de onde construir.
- Props so entram em `corner`, `edge`, `dead_zone`, `pocket`. Nunca em `path`/`path_margin`.
- Props grandes ficam em bordas e cantos. O interior ganha identidade com terreno tonal (`terrain_tints`), nao com objetos soltos.
- Cenario em massa coerente (bosque, ruina, pantano, neve), nao objetos isolados aleatorios.
- Se a rota ocupa quase todas as bordas (ex.: `icarusfalls`), priorizar backdrops nas extremidades e terreno tonal.
- **Nunca usar pedaco de peca composta como prop avulso** (ver ASSET_MAP > Pecas compostas).
- Nao recortar os `game_background_N.png` compostos: eles ja trazem estrada propria, que nao bate com os `map.xml`.

### Notas de `build_maps.py`

- `THEMES[*]["road"]` aponta para a reta horizontal de cada familia (`tail_2`: `6`; `tail_1`/`tail_4`/`tail_7`: `8`), porque os ids `5`–`8` mudam de ordem. Antes era `6` em todos, o que funcionava so porque `road_surface_fill()` usa apenas o miolo do tile.
- Os pools so contem props isolados, conferidos contra os `.tmx`. Pedacos de pecas compostas (moinhos, bosques 2x2, torre 22/23) ficam fora, e os comentarios dizem por que.

## 6. Animacoes Extras

### Prioridade alta

- [parcial] Torres com idle animado: as 3 magicas sim, a Arrow nao (secao 1)
- [feito] Projeteis melhores (secao 1)
- [feito] Inimigos com caminhada fluida: loop corrigido (secao 2)
- [parcial] Selecao pulsante no menu principal; demais menus pendentes
- [pendente] Botao/icone selecionado piscando

### Prioridade media

- [feito] Morte de inimigos (fade-out por codigo)
- [feito] Hit flash ao receber dano
- [pendente] Efeito de impacto do projetil (candidatos: `magic-effects-game-sprite`)
- [pendente] Visual de inicio de wave
- [pendente] Feedback no HUD ao ganhar ouro/perder vida

### Prioridade baixa

- Efeitos magicos grandes
- Particulas complexas
- Animacoes muito longas de menu
- Sprites grandes demais

### Restricoes tecnicas

- Frames `32x32` para gameplay.
- Evitar sprites gigantes.
- Spritesheets horizontais simples.
- Poucos frames por animacao no inicio.
- Testar memoria no PSP/emulador depois de cada lote.

## 7. Formato dos assets no jogo

Torres (`tower.xml`):

- `tower.png`: `128x32`, 4 frames `32x32` (`<TowerImg ... Frames="4" FrameTime=...>`)
- `ST_*.png`: `128x32`, 4 frames (`<Projectile ... Frames="4">`)
- `icon.png`: `32x32` (`<MenuIcon>`)

Inimigos (`enemy.xml`):

- sheet horizontal `384x32`, 12 frames `32x32` (`<EnemyImg ... Frames="12" FrameTime=...>`)

Mapas: ver secao 5.

UI: imagens pequenas ou tela inteira `480x272`, carregadas pelos paths de `Resource.cpp`.

### Passos para um asset novo

1. Escolher o asset fonte (ASSET_MAP).
2. Criar/ajustar o script em `tools/asset_pipeline/`.
3. Reduzir para o tamanho PSP, removendo sombra/fundo se precisar.
4. Montar o spritesheet horizontal RGBA.
5. Atualizar o XML (frames, `FrameTime`).
6. Rodar no emulador (`make` + PPSSPP).
7. Ajustar escala, centro e legibilidade.

## 8. Ordem de Implementacao

### Fase 1 - Prova visual rapida — [feito]

- Uma torre, um inimigo e um icone de HUD trocados. Na pratica a fase foi alem disso (ver Fase 2).

### Fase 2 - Gameplay visual completo — [parcial]

- [feito] As 4 torres (sprite estatico).
- [feito] Projeteis.
- [feito] Os 7 inimigos (o plano pedia 3).
- [feito] Menu lateral e upgrade bar.
- [feito] Mapas re-renderizados (secao 5).
- [feito] Idle das torres magicas, loop dos inimigos.
- [pendente] Idle da Arrow Tower, barra de vida, range circle, cursor.

### Fase 3 - Menus profissionais — [parcial]

- [feito] `MainMenuScreen`: botoes de madeira/metal e selecao dourada pulsante.
- Proximo passo: `PauseScreen`, depois `GameOptionsScreen` (selecao de mapa).
- Respeitar os assets protegidos e as restricoes da secao 4.
- Win/derrota: fora do escopo.

### Fase 4 - Polimento — [pendente]

- Animacoes extras.
- Feedback visual de dano, gold e wave.
- Ajuste fino de contraste.
- Otimizacao de memoria.
- Padronizacao final dos assets.

## Decisao de Direcao Artistica

A melhor direcao para `Gods Defense` e combinar o tema mitologico atual com fantasia tower defense cartunesca:

- deuses e monstros continuam sendo a identidade
- assets novos entram como base visual profissional
- torres podem parecer estruturas de templo, magia e guerra
- UI usa madeira, metal, pedra e ouro
- animacoes devem melhorar leitura e impacto, nao virar ruido visual
