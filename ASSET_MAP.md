# Asset Map — Tower Defense 2D Game Kit v1.1

> Fonte: `tower-defense-2d-game-kit-v1.1/`  
> Licença: [craftpix.net/file-licenses](https://craftpix.net/file-licenses/)  
> Total de arquivos PNG: ~5.800  
> Gerado em: 2026-05-16

---

## Índice

1. [Monstros — 4 Packs](#monstros--4-packs)
   - [2d-monster-sprites](#1-2d-monster-sprites)
   - [monster-enemy-game-sprites](#2-monster-enemy-game-sprites)
   - [monster-character-2d-sprites](#3-monster-character-2d-sprites)
   - [tower-defense-monster-2d-sprites](#4-tower-defense-monster-2d-sprites)
2. [Torres — 4 Tipos](#torres--4-tipos)
   - [archer-tower-game-assets](#1-archer-tower-game-assets)
   - [magic-tower-game-assets](#2-magic-tower-game-assets)
   - [stone-tower-game-assets](#3-stone-tower-game-assets)
   - [support-tower-game-assets](#4-support-tower-game-assets)
3. [Efeitos Mágicos](#efeitos-mágicos--magic-effects-game-sprite)
4. [GUI](#gui--td-gui)
5. [Tilesets](#tilesets--td-tilesets)
6. [Formatos de Arquivo](#formatos-de-arquivo)
7. [Notas Importantes](#notas-importantes)

---

## Monstros — 4 Packs

O kit inclui **4 packs de inimigos** distintos, totalizando **40 variantes de monstros** (10 por pack). Cada pack tem estilo visual diferente mas convenção similar de animações.

---

### 1. `2d-monster-sprites`

**Caminho:** `2d-monster-sprites/PNG/{1-10}/`

- **10 monstros** numerados de 1 a 10
- **7 estados de animação** por monstro: `attack`, `die`, `hurt`, `idle`, `jump`, `run`, `walk`
- **20 frames** por animação (frames `000`–`019`)
- **Naming:** `{N}_enemies_1_{animation}_{frame}.png`
  - Exemplo: `1_enemies_1_attack_000.png`

| Animação | Frames | Uso típico |
|----------|--------|------------|
| `attack` | 20 | Monstro atacando |
| `die`    | 20 | Morte |
| `hurt`   | 20 | Tomando dano |
| `idle`   | 20 | Parado/esperando |
| `jump`   | 20 | Pulando |
| `run`    | 20 | Correndo rápido |
| `walk`   | 20 | Andando |

**Arquivos fonte disponíveis:**
- `AI/enemies_3.ai` — arquivo Adobe Illustrator
- `EPS/enemies_3.eps` — arquivo vetorial EPS
- `SCML/{1-10}/{N}.scml` — projeto Spriter (animação esqueletal)
  - Obs: monster 7 tem `.autosave.scml` adicional

---

### 2. `monster-enemy-game-sprites`

**Caminho:** `monster-enemy-game-sprites/PNG/{1-10}/`

- **10 monstros** numerados de 1 a 10
- **7 estados de animação** por monstro: `attack`, `die`, `hurt`, `idle`, `jump`, `run`, `walk`
- **20 frames** por animação (frames `000`–`019`)
- **Naming:** `{N}_enemies_1_{animation}_{frame}.png`
  - Exemplo: `3_enemies_1_run_005.png`

Estrutura idêntica ao `2d-monster-sprites` mas com visuais diferentes.

**Arquivos fonte disponíveis:**
- `AI/` — arquivo Adobe Illustrator
- `EPS/` — 1 EPS consolidado
- `SCML/{1-10}/{N}.scml` — projetos Spriter

---

### 3. `monster-character-2d-sprites`

**Caminho:** `monster-character-2d-sprites/PNG/{1-10}/`

- **10 monstros** numerados de 1 a 10
- **6 estados de animação** por monstro: `ATTACK`, `DIE`, `HURT`, `JUMP`, `RUN`, `WALK`
  - ⚠️ **Sem `IDLE`** neste pack
  - ⚠️ Monster **8** não tem animação `JUMP`
- **10 frames** por animação (frames `000`–`009`)
- **⚠️ Anomalia de naming:** todos os arquivos dentro de qualquer pasta `{N}/` têm o prefixo fixo `2_enemies_1_` no nome (não refletem o número da pasta)
  - Exemplo dentro de `PNG/5/`: `2_enemies_1_ATTACK_000.png` (não `5_enemies_1_...`)

**Arquivos fonte disponíveis:**
- `AI/` — arquivo Adobe Illustrator
- `EPS/` — **65 EPS** organizados por pasta `EPS/{1-10}/` (fontes por monstro)
- `SCML/{1-10}/{N}.scml` — projetos Spriter

---

### 4. `tower-defense-monster-2d-sprites`

**Caminho:** `tower-defense-monster-2d-sprites/PNG/{1-10}/`

- **10 monstros** numerados de 1 a 10
- **6 estados de animação** por monstro: `ATTACK`, `DIE`, `HURT`, `JUMP`, `RUN`, `WALK`
  - ⚠️ **Sem `IDLE`** neste pack
  - ⚠️ Monster **10** não tem animação `JUMP`
- **10 frames** por animação (frames `000`–`009`)
- **⚠️ Anomalia de naming:** todos os arquivos têm prefixo fixo `1_enemies_1_` independente da pasta
  - Exemplo dentro de `PNG/7/`: `1_enemies_1_RUN_000.png`

**Arquivos fonte disponíveis:**
- `AI/` — arquivo Adobe Illustrator
- `EPS/` — **67 EPS** organizados em `EPS/{1-10}/`
- `SCML/{1-10}/{N}.scml` — projetos Spriter

---

## Torres — 4 Tipos

Os assets de torre são sequências de frames numerados (`1.png`, `2.png`, ...) que representam a animação/construção da torre em seus vários estágios ou estados. Cada torre tem também arquivo Adobe Illustrator e EPS (vetorial editável).

---

### 1. `archer-tower-game-assets`

**Caminho:** `archer-tower-game-assets/PNG/`

- **54 frames** numerados (`1.png` a `54.png`)
- **4 folhas compostas:**
  - `All.png` — todas as versões em uma imagem
  - `All_v2.png` — versão 2 da folha composta
  - `All_without_a_shadow.png` — sem sombra
  - `All_without_a_shadow-v2.png` — versão 2 sem sombra

**Arquivos fonte:**
- `AI/` — Adobe Illustrator
- `EPS/` — EPS vetorial
- `FLA/` — Adobe Flash/Animate (animação)

---

### 2. `magic-tower-game-assets`

**Caminho:** `magic-tower-game-assets/PNG/`

- **31 frames** numerados (`1.png` a `31.png`)
- **1 folha especial:** `without_a_shadow.png`

**Arquivos fonte:**
- `AI/` — Adobe Illustrator
- `EPS/` — EPS vetorial
- `FLA/` — Adobe Flash/Animate

---

### 3. `stone-tower-game-assets`

**Caminho:** `stone-tower-game-assets/PNG/`

- **61 frames** numerados (`1.png` a `61.png`)
- Sem folhas compostas adicionais

**Arquivos fonte:**
- `AI/` — Adobe Illustrator
- `EPS/` — EPS vetorial
- `FLA/` — Adobe Flash/Animate

---

### 4. `support-tower-game-assets`

**Caminho:** `support-tower-game-assets/PNG/`

- **17 frames** numerados (`1.png` a `17.png`)
- **1 folha especial:** `without_a_shadow.png`

**Arquivos fonte:**
- `AI/` — Adobe Illustrator
- `EPS/` — EPS vetorial
- (sem FLA neste pack)

---

## Efeitos Mágicos — `magic-effects-game-sprite`

**Caminho base:** `magic-effects-game-sprite/PNG/`

9 efeitos animados + 1 pasta de ícones estáticos:

| Pasta | Frames | Naming | Descrição |
|-------|--------|--------|-----------|
| `damage/` | 10 | `1_effect_damage_000.png` | Efeito de dano |
| `def/` | 10 | `1_effect_def_000.png` | Efeito de defesa/escudo |
| `fire/` | 19 | `1_effect_fire_000.png` | Fogo |
| `freeze/` | 16 | `1_effect_freeze_000.png` | Gelo/congelamento |
| `rain/` | 39 | `1_effect_rain_001.png` | Chuva (começa em `001`) |
| `stone/` | 18 | `1_effect_stone_000.png` | Pedra/terra |
| `time/` | 14 | `1_effect_time_000.png` | Efeito de tempo/slow |
| `zip/` | 14 | `1_effect_zip_000.png` | Relâmpago/electricidade |
| `icons/` | 8 | `1.png` a `8.png` | Ícones estáticos de efeito |

**Arquivos fonte:**
- `AI/` — Adobe Illustrator (1 arquivo)
- `EPS/` — **82 EPS** em subpastas: `damage/`, `def/`, `fire/`, `fire_2/`, `freeze/`, `icons/`, `rain/`, `stone/`, `time/`, `zip/`
  - ⚠️ Existe `fire_2/` nos EPS mas **não tem pasta correspondente nos PNGs** — variante extra de fogo apenas no EPS
- `SCML/effect/` — **74 PNGs** de peças do sprite sheet Spriter + `freeze.scml` (projeto Spriter para o efeito de freeze)

---

## GUI — `td-gui`

**Caminho base:** `td-gui/PNG/`

13 telas/componentes de interface completos:

| Pasta | PNGs | Componentes principais |
|-------|------|----------------------|
| `achievement/` | 13 | bg, header, window, table, star, button_close, preview |
| `difficulty/` | 10 | bg, window, table, buttons (easy/normal/hard), header, preview |
| `empty_table/` | 6 | bg, table_1 a table_4, preview |
| `failed/` | 8 | bg, window, table, header, button_restart, button_left, preview |
| `interface_game/` | 27 | bg, bars (1-4), bg_bar, buttons (pause/quick/start), heart, ícones (ico_1-8), skull, star, table, zip, skull_arr/bg, je, preview |
| `levels/` | 23 | bg, table, header, buttons (left/right/close/empty), stars (1-4), números (0-9 exceto 2), preview |
| `load_bar/` | 6 | bg, dark, load_bar_1, load_bar_2, load_bar_bg, preview |
| `menu/` | 16 | bg, logo, dark, rope_small, buttons: play, registration, settings, sound, sound_off, music, music_off, facebook, google, twitter, vk, preview |
| `registration/` | 14 | bg, window, header, dark, rope_big, table_1, table_2, buttons (create/close/facebook/google/twitter/vk), preview |
| `settings/` | 19 | bg, window_1, window_2, table, header, dark, rope_big, bar, bar_bg, buttons (close/plus/minus/on/off/facebook/google/twitter/vk), preview |
| `shop/` | 24 | bg, window_1, window_2, table, header, dark, rope_big, button_close, button_empty, crystals (1-3), números, zip, preview |
| `upgrade/` | 39 | bg, window, table, header, dark, rope_big, buttons (close/done/reset), line, star, undo, ícones ico_1 a ico_24, preview |
| `win/` | 13 | bg, window, table, header, dark, stars (1-4), buttons (menu/right), zip, preview |

**Arquivos fonte:**
- `AI/` — Adobe Illustrator
- `EPS/` — EPS vetorial
- **Fonte tipográfica usada:** Dimbo (`https://www.dafont.com/dimbo.font`)

> Os demais packs usam a fonte **Chisel Mark** (`https://www.dafont.com/chisel-mark.font`)

---

## Tilesets — `td-tilesets`

3 variantes de tilesets com 4 temas de mapa cada:

---

### Tileset Pack 1 — `tower-defense-game-tilesets`

**Caminho:** `td-tilesets/tower-defense-game-tilesets/PNG/`

4 mapas completos, cada um com imagem composta + layers separados:

#### `game_background_1/` — Floresta com rio
- **Composto:** `game_background_1.png`
- **Layers:** `main_bg`, `land`, `bridge`, `fence`, `bush`, `stone`, `tree`, `tree_2`, `river_1` a `river_6`, `road_1` a `road_10`, `decor_1` a `decor_5`, `dot`

#### `game_background_2/` — Lago e pedras
- **Composto:** `game_background_2.png`
- **Layers:** `main_bg`, `land`, `lake`, `stone_1`, `stone_2`, `stone_3`, `road_1` a `road_10`, `decor_1` a `decor_9`, `dot`

#### `game_background_3/` — Rio com ponte
- **Composto:** `game_background_3.png`
- **Layers:** `main_bg`, `land`, `bridge`, `stone`, `river_1` a `river_6`, `road_1` a `road_10`, `decor_1` a `decor_8`, `dot`

#### `game_background_4/` — Montanhas
- **Composto:** `game_background_4.png`
- **Layers:** `main_bg`, `land`, `mountains`, `stone`, `tree`, `road_1` a `road_10`, `decor_1` a `decor_3`, `dot`

**Arquivos fonte:** `AI/` + `EPS/`

---

### Tileset Pack 2 — `tower-defense-game-tile-set-pack-2`

**Caminho:** `td-tilesets/tower-defense-game-tile-set-pack-2/PNG/`

4 mapas com layers organizados em subpasta numerada (`layers/{N}/road_*.png`):

#### `game_background_1/` — Floresta com lago
- **Composto:** `game_background_1.png`
- **Layers:** `main_bg`, `land`, `lake`, `stone`, `tree_1`, `tree_2`, `bush_1` a `bush_3`, `road_1` a `road_10` (em `layers/1/`), `decor_1` a `decor_5`, `dot`

#### `game_background_2/` — Lago com pedras
- **Composto:** `game_background_2.png`
- **Layers:** `main_bg`, `land`, `lake_1` a `lake_3`, `stone_1` a `stone_8`, `road_1` a `road_10` (em `layers/2/`), `decor_1` a `decor_7`, `dot`

#### `game_background_3/` — Rio e ponte com lago
- **Composto:** `game_background_3.png`
- **Layers:** `main_bg`, `land`, `lake`, `bridge`, `river_1` a `river_6`, `stone_1`, `stone_2`, `tree_1`, `tree_2`, `road_1` a `road_10` (em `layers/3/`), `decor_1` a `decor_6`, `dot`

#### `game_background_4/` — Árvores e lagos
- **Composto:** `game_background_4.png`
- **Layers:** `main_bg`, `land`, `lake_1` a `lake_3`, `stone_1` a `stone_4`, `tree_1` a `tree_3`, `road_1` a `road_10` (em `layers/4/`), `decor_1` a `decor_3`, `dot`

**Arquivos fonte:** `AI/` + `EPS/`

---

### Tiled Version — `version-for-the-program-Tiled`

**Caminho:** `td-tilesets/version-for-the-program-Tiled/`

Versão dos tilesets otimizada para o editor **Tiled Map Editor** (`.tmx`):

| Tileset | Tiles individuais | Arquivo Tiled |
|---------|------------------|---------------|
| `tail_1` | 49 PNGs | `tailed/tail_1.tmx` |
| `tail_2` | 56 PNGs | `tailed/tail_2.tmx` |
| `tail_3` | 49 PNGs | `tailed/tail_3.tmx` |
| `tail_4` | 46 PNGs | `tailed/tail_4.tmx` |
| `tail_5` | 42 PNGs | `tailed/tail_5.tmx` |
| `tail_6` | 45 PNGs | `tailed/tail_6.tmx` |
| `tail_7` | 40 PNGs | `tailed/tail_7.tmx` |
| `tail_8` | 47 PNGs | `tailed/tail_8.tmx` |

- Tiles numerados (`1.png`, `2.png`, ...)
- **Arquivos fonte:** `AI/tail_1.ai` a `AI/tail_8.ai`

#### Mapa operacional dos tiles de caminho

Os arquivos `tailed/tail_*.tmx` confirmam a ordem dos tiles, mas nao trazem nomes semanticos como `straight` ou `corner`. Para a pipeline do jogo, usar a convencao visual abaixo para os `PNG/tail_N/{id}.png`.

Essa convencao vale para as familias `tail_1`, `tail_2`, `tail_4`, `tail_6`, `tail_7` e `tail_8`; elas repetem o mesmo bloco estrutural nos ids `1` a `12`, mudando apenas o tema visual.

| Tile id | Uso operacional | Conectividade confirmada |
|---:|---|---|
| `1` | curva | `S + E` |
| `2` | curva | `S + W` |
| `3` | curva | `N + E` |
| `4` | curva | `N + W` |
| `5` | reta vertical | norte-sul |
| `6` | reta horizontal | oeste-leste |
| `7` | T sem norte | `S + W + E` |
| `8` | cruzamento | `N + S + W + E` |
| `9` | reta horizontal alternativa | oeste-leste |
| `10` | curva alternativa | `S + W` |
| `11` | T sem oeste | `N + S + E` |
| `12` | T sem sul | `N + W + E` |

Uso recomendado na pipeline:

- Nao recortar `game_background_N.png` composto para mapas jogaveis com rota propria. Esses backgrounds ja contem estradas/decoracoes prontas e ficam incoerentes quando combinados com os `map.xml` existentes.
- Para mapas de gameplay, montar um tilemap por celula `32x32` a partir do `CollisionMap`.
- Usar os tiles `1` a `12` apenas para caminho, escolhidos por conectividade da celula (`N`, `S`, `E`, `W`).
- Para o caso `N + S + W`, que nao tem tile dedicado nas familias verificadas, a pipeline pode reutilizar `11` rotacionado 180 graus.
- Alternativa atualmente usada por `tools/asset_pipeline/build_maps.py`: gerar a estrada como um tracado continuo texturizado a partir dos checkpoints de `<Path>`. Isso evita curvas quebradas quando os PNGs `256x256` do Tiled nao fecham bem apos reducao para celulas `32x32`.
- Ao usar esse tracado continuo, nao preencher a estrada com o tile de caminho inteiro: os tiles carregam bordas e cantos internos que viram padroes repetidos. A pipeline deve usar apenas o miolo do tile como textura de superficie e desenhar borda/sombra separadamente.
- Usar tiles de base separados para areas construiveis e decoracoes, por tema:

| Tema | Familia | Base sugerida | Decoracoes seguras |
|---|---|---:|---|
| grama/selva | `tail_1` ou `tail_5` | `42` ou `22` | `30`, `31`, `33`, `35`, `36`, `37`, `43`-`49` |
| areia/ruinas | `tail_2` | `21` | `22`-`24`, `28`-`40`, `41`-`56` |
| neve/gelo | `tail_4` | `35` ou `44` | `21`-`29`, `33`, `34`, `38`-`43` |
| lava/pedra | `tail_6` | `24` | `20`-`32`, `37`-`45` |
| pantano/pedra | `tail_7` | `26` | `23`-`25`, `27`-`40` |
| pedra/musgo | `tail_8` | `34` | `19`-`27`, `29`-`47` |

#### Referencia rapida de decoracao por familia

Use esta tabela antes de mexer em `tools/asset_pipeline/build_maps.py`. Ela separa os tiles por funcao visual para evitar decoracao aleatoria sem sentido em areas construiveis.

| Familia | Funcao | Tile ids |
|---|---|---|
| `tail_1` grama/vila | base limpa | `42` |
| `tail_1` grama/vila | agua/ponte/trilha pronta | `13`-`18`, `25`-`27` |
| `tail_1` grama/vila | props de vila | `20`, `21`, `28`, `29`, `38`, `39`, `40`, `41` |
| `tail_1` grama/vila | pedras/flor/arbustos pequenos | `22`-`24`, `30`-`32`, `35`, `36`, `47`-`49` |
| `tail_1` grama/vila | arvores/massa verde | `33`, `34`, `37`, `43`-`46` |
| `tail_2` areia/ruinas | base limpa | `21` |
| `tail_2` areia/ruinas | agua/ponte/trilha pronta | `13`-`20`, `25`, `27`, `55` |
| `tail_2` areia/ruinas | ruinas/templo/vila | `43`-`49`, `56` |
| `tail_2` areia/ruinas | cactos/ossos/arvores secas | `29`, `31`-`36`, `41`, `42`, `50`-`54` |
| `tail_2` areia/ruinas | pedras/folhagem seca | `22`-`24`, `28`, `30`, `37`-`40` |
| `tail_4` neve/gelo | base limpa | `35` |
| `tail_4` neve/gelo | gelo/agua/ponte/trilha pronta | `13`-`20`, `30` |
| `tail_4` neve/gelo | construcao/ruina | `21`-`23`, `31`, `32` |
| `tail_4` neve/gelo | pinheiros | `24`-`29` |
| `tail_4` neve/gelo | pedras/neve baixa | `33`, `34`, `38`-`43` |
| `tail_7` pantano/pedra | base limpa | `26` |
| `tail_7` pantano/pedra | agua/pantano/ponte | `13`-`24` |
| `tail_7` pantano/pedra | arvores mortas/massa pantano | `35`-`40` |
| `tail_7` pantano/pedra | pedras/ossos/nevoa baixa | `27`-`34` |

Layouts de mapa recomendados:

- `olympus`: areia/ruinas (`tail_2`) com clusters de templo, cactos, ossos e pedras. Evitar arvores verdes.
- `icarusfalls`: pantano/pedra (`tail_7`) com arvores mortas nas bordas, pedras e ossos em pequenos grupos. Evitar props de vila.
- `rescueathena`: grama/vila (`tail_1`) com bosques nas bordas, poucos props de vila e pedras/arbustos em grupos.
- `icymanipulator`: neve/gelo (`tail_4`) com pinheiros, cabana/ruina e rochas de neve agrupadas.

Regra de composicao para gameplay:

- Nao colocar props opacos no miolo da area construivel. Eles parecem obstaculo e atrapalham a leitura de onde construir.
- Props grandes devem ficar em bordas, cantos ou como camada de fundo parcialmente coberta pela estrada.
- Para dar identidade ao interior do mapa, usar manchas suaves de terreno, variacao de cor e textura baixa, nao objetos soltos.
- Se uma rota ocupa quase todas as bordas, como `icarusfalls`, priorizar backdrops nas extremidades e terreno tonal; nao forcar arvores/pedras dentro dos bolsões de construcao.

Observacao importante: antes de trocar a arte final de mapa, validar uma folha de preview da combinacao `CollisionMap` + tiles escolhidos. Se os ids de curva ficarem visualmente invertidos para alguma familia, corrigir a tabela acima e a pipeline, nao compensar com recortes manuais.

---

## Formatos de Arquivo

| Extensão | Descrição | Onde aparece |
|----------|-----------|-------------|
| `.png` | Sprites/frames prontos para uso | Todos os packs |
| `.ai` | Adobe Illustrator (vetor editável) | Todos os packs |
| `.eps` | Encapsulated PostScript (vetor) | Todos os packs |
| `.fla` | Adobe Flash/Animate (animação timeline) | Torres (archer, magic, stone) |
| `.scml` | Projeto Spriter (animação esqueletal) | Packs de monstros, magic-effects |
| `.tmx` | Projeto Tiled Map Editor | td-tilesets/version-for-the-program-Tiled |

---

## Notas Importantes

### Anomalias de Naming

1. **`monster-character-2d-sprites`:** todos os arquivos dentro de qualquer pasta `PNG/{N}/` têm prefixo `2_enemies_1_` no nome, independente do número do monstro. Para identificar qual monstro, use o número da **pasta**, não do arquivo.

2. **`tower-defense-monster-2d-sprites`:** mesmo problema — prefixo fixo `1_enemies_1_` em todos os arquivos. Identificar pelo número da **pasta**.

3. **`magic-effects-game-sprite`:** existe subpasta `fire_2/` nos EPS (variante alternativa de fogo) sem correspondente na pasta PNG.

### Convenções de Animação

| Pack | Animações | Frames | Tem IDLE? |
|------|-----------|--------|-----------|
| `2d-monster-sprites` | attack, die, hurt, idle, jump, run, walk | 20 | ✅ |
| `monster-enemy-game-sprites` | attack, die, hurt, idle, jump, run, walk | 20 | ✅ |
| `monster-character-2d-sprites` | ATTACK, DIE, HURT, JUMP, RUN, WALK | 10 | ❌ |
| `tower-defense-monster-2d-sprites` | ATTACK, DIE, HURT, JUMP, RUN, WALK | 10 | ❌ |

### Rotas de Importação para o Jogo

Para usar um monstro em código, o padrão de path é:

```
# Pack 1 ou 2 (20 frames, tem idle)
tower-defense-2d-game-kit-v1.1/{pack}/PNG/{monster_num}/{monster_num}_enemies_1_{animation}_{frame:03d}.png

# Pack 3 ou 4 (10 frames, sem idle — atenção ao naming bugado)
tower-defense-2d-game-kit-v1.1/{pack}/PNG/{monster_num}/2_enemies_1_{ANIMATION}_{frame:03d}.png  # pack 3
tower-defense-2d-game-kit-v1.1/{pack}/PNG/{monster_num}/1_enemies_1_{ANIMATION}_{frame:03d}.png  # pack 4
```

Para um tileset layer individual (pack 1):
```
tower-defense-2d-game-kit-v1.1/td-tilesets/tower-defense-game-tilesets/PNG/game_background_{N}/layers/{layer_name}.png
```
