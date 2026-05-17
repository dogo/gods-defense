# Plano de Evolucao Visual - Gods Defense

## Objetivo

Atualizar o visual do jogo usando o pacote `tower-defense-2d-game-kit-v1.1`, mantendo o tema mitologico/fantasia de `Gods Defense`, mas deixando a apresentacao mais profissional, animada e consistente no PSP.

A direcao geral deve ser: fantasia cartunesca, clara, com leitura boa em tela pequena, sem perder a identidade de deuses, monstros e defesa de templo.

## 1. Torres

### Objetivo visual

As torres precisam parecer mais fortes, distintas entre si e legiveis em `32x32`. Cada torre deve comunicar sua funcao sem depender de texto.

### Assets candidatos

- `archer-tower-game-assets`
- `magic-tower-game-assets`
- `stone-tower-game-assets`
- `support-tower-game-assets`
- `magic-effects-game-sprite/PNG/icons` para icones auxiliares, se necessario

### Mapeamento sugerido

| Torre atual | Nova direcao |
|---|---|
| Arrow Tower | Torre arqueira / balista |
| Fire Tower | Torre magica vermelha / chama |
| Ice Tower | Torre cristalina azul / gelo |
| Lightning Tower | Torre magica eletrica / raio |

### Melhorias propostas

- Criar spritesheets `tower.png` com mais frames.
- Manter compatibilidade inicial com 4 frames, depois expandir se necessario.
- Adicionar animacao idle leve:
  - chama pulsando na torre de fogo
  - cristal brilhando na torre de gelo
  - raio piscando na torre eletrica
  - arqueiro/balista tensionando levemente
- Criar `icon.png` novo para cada torre no menu lateral.
- Criar projeteis novos:
  - flecha
  - bola de fogo
  - cristal/gelo
  - raio curto

### Entregaveis

- `PSP Project/Res/towers/arrow/tower.png`
- `PSP Project/Res/towers/fire/tower.png`
- `PSP Project/Res/towers/ice/tower.png`
- `PSP Project/Res/towers/lightning/tower.png`
- Novos `icon.png`
- Novos `ST_*.png`
- Ajustes nos `tower.xml` se aumentarmos frames, `FrameTime` ou dimensoes

## 2. Inimigos

### Objetivo visual

Os inimigos devem parecer parte de um exercito mitologico/fantasia, com silhuetas diferentes e movimento mais vivo.

### Assets candidatos

- `2d-monster-sprites`
- `monster-enemy-game-sprites`
- `tower-defense-monster-2d-sprites`
- `monster-character-2d-sprites`

### Mapeamento sugerido

| Inimigo atual | Nova direcao |
|---|---|
| Minions | Criaturas pequenas / soldados fracos |
| Medusa | Maga/monstro elite |
| Minotaur | Bruto terrestre |
| Cyclops | Tanque lento |
| Cerberus | Monstro rapido terrestre |
| Griffin | Inimigo voador |
| Hydra | Boss grande |

### Melhorias propostas

- Trocar spritesheets atuais `384x32` por spritesheets novos.
- Comecar com animacao de movimento:
  - `walk` ou `run`
  - 12 frames em `32x32`
- Depois adicionar estados extras:
  - `hurt`
  - `die`
  - possivelmente `attack`, se houver combate visual no futuro
- Ajustar velocidade visual por tipo:
  - inimigos rapidos usam `run`
  - inimigos pesados usam `walk`
  - bosses usam menos frames, mas maior presenca
- Melhorar barra de vida:
  - barra menor e mais polida
  - borda escura
  - cor muda conforme vida baixa

### Entregaveis

- Novos PNGs em `PSP Project/Res/enemies/*`
- Ajustes nos `enemy.xml`
- Possivel expansao do renderer para suportar animacao de morte/hit depois

## 3. UI Ingame / HUD

### Objetivo visual

A UI ingame deve parecer menos prototipo e mais jogo final, mas sem ocupar espaco demais na tela `480x272`.

### Assets candidatos

- `td-gui/PNG/interface_game`
- `td-gui/PNG/upgrade`
- `td-gui/PNG/shop`
- `td-gui/PNG/empty_table`

### Areas atuais

- `hud.png`
- `sidebar.png`
- `upgradebar.png`
- `selector.png`
- `sell.png`
- `upgrade.png`
- cursor

### Melhorias propostas

- Redesenhar HUD superior com:
  - icone de ouro/cristal
  - icone de vida/coracao
  - texto mais legivel
- Atualizar menu lateral de torres:
  - fundo mais elegante
  - selecao mais clara
  - icones novos das torres
  - custo em destaque
- Atualizar barra de upgrade/venda:
  - botoes com icones mais claros
  - destaque visual para opcao selecionada
- Adicionar feedback visual:
  - tower placement com preview mais limpo
  - range circle menos bruto
  - feedback quando nao pode construir
- Possivel animacao:
  - selector piscando suavemente
  - icones de torre com leve destaque quando selecionados
  - botao de start wave animado

### Entregaveis

- Novos PNGs compactados para PSP
- Ajustes em `PSP Project/Src/GameGUI.cpp`
- Possivel ajuste em `PSP Project/Include/Resource.h`

## 4. Menus

### Objetivo visual

Os menus devem passar uma primeira impressao mais profissional. Hoje o jogo tem varias telas separadas; podemos unificar o estilo visual.

### Assets candidatos

- `td-gui/PNG/menu`
- `td-gui/PNG/levels`
- `td-gui/PNG/settings`
- `td-gui/PNG/difficulty`
- `td-gui/PNG/win`
- `td-gui/PNG/failed`
- `td-gui/PNG/load_bar`

### Telas a atualizar

- Title Screen
- Anykey Screen
- Main Menu
- Map Selection
- Pause
- Help
- About
- Trophies
- Win/Ending
- Exit Confirmation
- Memory Warning

### Melhorias propostas

- Criar background principal em `480x272`.
- Criar logo/titulo mais integrado ao tema `Gods Defense`.
- Substituir botoes de texto puro por botoes visuais.
- Usar uma linguagem visual consistente:
  - madeira/pedra/metal
  - brilho dourado
  - icones claros
- Adicionar transicoes simples:
  - fade in/fade out
  - botao selecionado pulsando
  - seta/selector animado
- Tela de vitoria/derrota:
  - usar assets `win` e `failed`
  - adicionar estrelas ou score visual
- Tela de mapa:
  - melhorar cards/preview dos mapas
  - destacar nome, descricao e miniatura

### Entregaveis

- Backgrounds `480x272`
- Botoes reduzidos para PSP
- Ajustes nas classes de tela em `PSP Project/Src/*Screen.cpp`

## 5. Mapas e Ambiente

### Objetivo visual

Os mapas precisam continuar legiveis para tower defense, mas podem ganhar acabamento melhor e mais vida.

### Assets candidatos

- `td-tilesets/tower-defense-game-tilesets`
- `td-tilesets/tower-defense-game-tile-set-pack-2`
- `td-gui/PNG/interface_game/bg.png` como referencia visual, nao como asset direto

### Melhorias propostas

- Criar pelo menos um mapa novo com tiles do pacote.
- Manter grid e areas construiveis claras.
- Evitar excesso de detalhe onde inimigos passam.
- Adicionar decoracoes:
  - pedras
  - arvores
  - ruinas
  - agua
  - templos
- Tema recomendado:
  - ilha/selva mitologica
  - ruinas de templo
  - caminho de invasao ate santuario

### Entregaveis

- Novo mapa PNG `480x?` conforme sistema atual
- `mini.png`
- `map.xml`
- Possivel atualizacao no MapGenerator depois

## 6. Animacoes Extras

### Objetivo

Adicionar vida ao jogo sem comprometer performance no PSP.

### Prioridade alta

- Torres com idle animado
- Projeteis melhores
- Inimigos com caminhada mais fluida
- Selector animado no menu
- Botao/icone selecionado piscando

### Prioridade media

- Morte de inimigos
- Hit flash quando recebe dano
- Efeito pequeno de impacto do projetil
- Wave start visual
- HUD com feedback ao ganhar ouro/perder vida

### Prioridade baixa

- Efeitos magicos grandes
- Particulas complexas
- Animacoes muito longas de menu
- Sprites grandes demais

### Restricoes tecnicas

- Preferir frames `32x32` para gameplay.
- Evitar sprites gigantes.
- Usar spritesheets horizontais simples.
- Manter poucos frames por animacao inicialmente.
- Testar memoria no PSP/emulador depois de cada lote.

## 7. Pipeline de Conversao

### Formato atual do jogo

Torres:

- `tower.png`: `128x32`
- 4 frames de `32x32`
- `icon.png`: `32x32`
- configurado via `tower.xml`

Inimigos:

- spritesheet horizontal
- exemplo atual: `384x32`
- 12 frames de `32x32`
- configurado via `enemy.xml`

UI:

- imagens pequenas ou tela inteira `480x272`
- carregadas via `Resource`

### Pipeline recomendado

1. Escolher assets fonte.
2. Reduzir para tamanho PSP.
3. Remover sombra preta/fundo indesejado quando necessario.
4. Montar spritesheet horizontal.
5. Salvar em PNG RGBA.
6. Atualizar XML.
7. Rodar no emulador.
8. Ajustar escala, centro, colisao visual e legibilidade.

## 8. Ordem de Implementacao

### Fase 1 - Prova visual rapida

- Trocar uma torre completa.
- Trocar um inimigo completo.
- Trocar um icone de HUD.
- Validar no jogo.

### Fase 2 - Gameplay visual completo

- Trocar as 4 torres.
- Trocar projeteis.
- Trocar 3 inimigos principais.
- Atualizar menu lateral e upgrade bar.

### Fase 3 - Menus profissionais

- Novo menu principal. Manter o asset atual `PSP Project/Res/background.png`; **nao alterar esse arquivo**.
- Nova tela de pausa.
- Nova tela de vitoria/derrota. **Adiado / fora do escopo agora**. Nao continuar tentando refazer `ending_win.png`, `ending_failed.png` ou `EndingScreen` nesta fase; a direcao visual ainda precisa ser definida antes.
- Nova tela de selecao de mapa.

Status adicional:

- Title Screen deve manter o asset atual `PSP Project/Res/GDSplash.png`; **nao alterar esse arquivo**.
- Anykey Screen deve manter o asset atual `PSP Project/Res/anykeylogo.png`; **nao alterar esse arquivo**.
- Nao usar `td-gui/PNG/win` ou `td-gui/PNG/failed` para as telas finais por enquanto; o resultado nao combina com a identidade atual do jogo.
- Proximo passo recomendado: aplicar a mesma linguagem visual em `PauseScreen`, `GameOptionsScreen` e tela de selecao de mapa.

### Fase 4 - Polimento

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
