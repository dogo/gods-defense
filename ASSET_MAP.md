# Asset Map — Tower Defense 2D Game Kit v1.1

> Fonte: `tower-defense-2d-game-kit-v1.1/` (todos os paths abaixo são relativos a essa pasta)
> Licença: [craftpix.net/file-licenses](https://craftpix.net/file-licenses/) (cada pack tem `TXT/license.txt` + `TXT/readme.txt`)
> Total: 5.887 arquivos, dos quais 5.476 PNG
> Validado contra o disco em: 2026-10-18

Este arquivo descreve **só o kit**. Decisões do jogo (qual asset vira o quê, regras de composição de mapa) ficam em `ASSET_UPGRADE_PLAN.md` e nos scripts de `tools/asset_pipeline/`.

---

## Índice

1. [Monstros — 4 Packs](#monstros--4-packs)
2. [Torres — 4 Tipos](#torres--4-tipos)
3. [Efeitos Mágicos](#efeitos-mágicos--magic-effects-game-sprite)
4. [GUI](#gui--td-gui)
5. [Tilesets](#tilesets--td-tilesets)
6. [Formatos de Arquivo](#formatos-de-arquivo)
7. [Notas Importantes](#notas-importantes)

---

## Monstros — 4 Packs

**4 packs × 10 monstros = 40 monstros.** Pastas `PNG/{1-10}/`, uma por monstro.

| Pack | Animações | Frames/anim | IDLE? | Prefixo do arquivo | AI / EPS |
|------|-----------|-------------|-------|--------------------|----------|
| `2d-monster-sprites` | `attack die hurt idle jump run walk` | 20 (`000`–`019`) | ✅ | `{N}_enemies_1_` (bate com a pasta) | `AI/enemies_3.ai`, `EPS/enemies_3.eps` |
| `monster-enemy-game-sprites` | `attack die hurt idle jump run walk` | 20 (`000`–`019`) | ✅ | `{N}_enemies_1_` (bate com a pasta) | `AI/enemies_4.ai`, `EPS/enemies_4.eps` |
| `monster-character-2d-sprites` | `ATTACK DIE HURT JUMP RUN WALK` | 10 (`000`–`009`) | ❌ | **sempre `2_enemies_1_`** | `AI/enemies_2.ai`, 65 EPS em `EPS/{1-10}/` |
| `tower-defense-monster-2d-sprites` | `ATTACK DIE HURT JUMP RUN WALK` | 10 (`000`–`009`) | ❌ | **sempre `1_enemies_1_`** | `AI/enemies_1.ai`, 67 EPS em `EPS/{1-10}/` |

Exceções:

- `monster-character-2d-sprites/PNG/8` não tem `JUMP`.
- `tower-defense-monster-2d-sprites/PNG/10` não tem `JUMP`.
- Nos packs 3 e 4 o prefixo do arquivo é fixo; identifique o monstro pelo número da **pasta**.

**SCML (Spriter):** todo pack tem `SCML/{N}/{N}.scml` mais os PNGs das peças do esqueleto em cada pasta. `2d-monster-sprites` também tem `SCML/7/7.autosave.scml`.

### ⚠️ Frames duplicados (verificado por hash)

Muitas animações repetem frames. Em uma sequência de 20, só 11 são únicos. Em uma de 10, só 6 são únicos. Ao amostrar frames, não espere que todos sejam diferentes.

- `2d-monster-sprites` (11/20): 1/hurt, 1/idle, 1/jump, 2/idle, 2/walk, 3/idle, 3/walk, 4/idle, 4/run, 5/idle, 8/hurt, 8/idle, 8/jump, 8/run, 9/hurt, 9/jump, 9/walk, 10/jump
- `monster-enemy-game-sprites` (11/20): 1/idle, 1/walk, 2/idle, 2/run, 5/idle, 6/idle, 8/idle, 9/idle
- `monster-character-2d-sprites` (6/10): `HURT`, `JUMP` e `WALK` em todos os monstros que têm a animação. `RUN` só em 2, 5, 6, 8 e 10.
- `tower-defense-monster-2d-sprites` (6/10): `HURT`, `JUMP`, `RUN` e `WALK` em quase todos. Exceções: 1/WALK tem 10 frames únicos, e o monstro 10 não tem `JUMP`.
- `ATTACK` e `DIE` não têm duplicatas em nenhum pack.

### ⚠️ Ciclos de 20 frames

O loop fecha em `019 → 000`. Pegar só um trecho (ex.: `000`–`011`) cria um salto visível na volta ao primeiro frame. Para reduzir o número de frames, amostre a sequência inteira em intervalos iguais.

---

## Torres — 4 Tipos

Os PNGs numerados (`1.png`, `2.png`, ...) são **peças avulsas**: variações de torre, níveis, arqueiros, projéteis etc. Não formam uma sequência de animação. Abra cada uma antes de usar.

| Pack | PNGs numerados | Folhas extras | AI / EPS | FLA |
|------|---------------:|---------------|----------|-----|
| `archer-tower-game-assets` | 54 (`1`–`54`) | `All.png`, `All_v2.png`, `All_without_a_shadow.png`, `All_without_a_shadow-v2.png` | `Archers_Tower_Game_assets` | `main_tower_5`–`8.fla` |
| `magic-tower-game-assets` | 31 (`1`–`31`) | `without_a_shadow.png` | `Magic_Tower_Game_assets` | `main_tower_9`–`12.fla` |
| `stone-tower-game-assets` | 61 (`1`–`61`) | — | `Stones_Tower_Game_assets` | `main_tower_1`–`4.fla` |
| `support-tower-game-assets` | 17 (`1`–`17`) | `without_a_shadow.png` | `Support_Tower_Game_assets` | — |

---

## Efeitos Mágicos — `magic-effects-game-sprite`

**Caminho base:** `magic-effects-game-sprite/PNG/`

| Pasta | Frames | Naming | Descrição |
|-------|-------:|--------|-----------|
| `damage/` | 10 | `1_effect_damage_000`–`009` | Dano |
| `def/` | 10 | `1_effect_def_000`–`009` | Defesa/escudo |
| `fire/` | 19 | `1_effect_fire_000`–`018` | Fogo |
| `freeze/` | 16 | `1_effect_freeze_000`–`015` | Gelo |
| `rain/` | 39 | `1_effect_rain_001`–`039` | Chuva (**começa em `001`**) |
| `stone/` | 18 | `1_effect_stone_000`–`017` | Pedra |
| `time/` | 14 | `1_effect_time_000`–`013` | Tempo/slow |
| `zip/` | 14 | `1_effect_zip_000`–`013` | Raio |
| `icons/` | 8 | `1.png`–`8.png` | Ícones estáticos |

**Arquivos fonte:**
- `AI/`: **10 arquivos**, um por efeito: `damage`, `def`, `fire`, `fire_2`, `freeze`, `icons`, `rain`, `stone`, `time`, `zip`.
- `EPS/`: **82 EPS** em subpastas: stone 16, fire_2 15, freeze 14, zip 13, fire 8, time 5, rain 4, damage 4, def 2, icons 1.
- ⚠️ `fire_2` existe em AI/EPS mas **não tem PNG**.
- `SCML/freeze.scml` (na raiz de `SCML/`) + `SCML/effect/` com **81 PNGs** de peças.

---

## GUI — `td-gui`

**Caminho base:** `td-gui/PNG/` · Fontes: `AI/{tela}.ai`, `EPS/{tela}.eps` (13 de cada) · Fonte tipográfica: **Dimbo** (`https://www.dafont.com/dimbo.font`)

> Os demais packs usam **Chisel Mark** (`https://www.dafont.com/chisel-mark.font`), conforme os `TXT/readme.txt`.

Lista completa dos arquivos (sem `.png`). Os nomes estão **exatamente** como no kit, inclusive os typos:

| Pasta | PNGs | Arquivos |
|-------|-----:|----------|
| `achievement/` | 13 | bg, button_close, dark, header_achievement, ico_j, normal_window, preview_achievement, rope_big, s_table, s_window, star, table, text_unlocked |
| `difficulty/` | 10 | bg, button_easy, button_empty_2, button_hard, button_normal, dark, header_diff, preview_difficulty, table, window |
| `empty_table/` | 6 | bg, preview_empty_table, table_1–4 |
| `failed/` | 8 | bg, button_left, button_restart, dark, header_failed, preview_failed, table, **wondow** |
| `interface_game/` | 27 | bar_1–4, bg, bg_bar, button_pause, button_quick, button_start, heart, ico_1–8, je, preview_interface_game, skull, skull_arr, skull_bg, star, table, table_down, zip |
| `levels/` | 23 | bg, **btton_empty**, button_close, button_left, button_right, dark, header_levels, num_ (sem dígito), num_0, num_1, num_3–9 (**sem num_2**), preview_levels, star_1–4, table |
| `load_bar/` | 6 | bg, dark, load_bar_1, load_bar_2, load_bar_bg, preview_load_bar |
| `menu/` | 16 | bg, **button__facebook**, button_google, button_music, button_music_off, button_play, button_registration, button_settings, button_sound, button_sound_off, button_twitter, button_vk, dark, logo, preview_menu, rope_small |
| `registration/` | 14 | bg, **button__facebook**, button_close, button_create, button_google, button_twitter, button_vk, dark, header_registration, preview_registration, rope_big, table_1, table_2, window |
| `settings/` | 19 | bar, bar_bg, bg, **button__facebook**, button_close, button_google, button_minus, button_off, button_on, button_plus, button_twitter, button_vk, dark, header_settings, preview_settings, rope_big, table, window_1, window_2 |
| `shop/` | 24 | bg, button_close, button_empty, crystal_1–3, dark, header_shop, num_ (sem dígito), num_0, num_1, num_3–9 (**sem num_2**), preview_shop, rope_big, table, window_1, window_2, zip |
| `upgrade/` | 39 | bg, button_close, button_done, button_reset, dark, header_upgrade, ico_1–24, line, preview_upgrade, rope_big, star, table, undo, **window_**, window_1, window_3 |
| `win/` | 13 | bg, button_menu, button_right, dark, header_win, preview_win, star_1–4, table, window, zip |

---

## Tilesets — `td-tilesets`

São 3 pastas: 2 packs de backgrounds prontos (4 cada) e 1 versão em tiles para o Tiled (8 tilesets).

### Tileset Pack 1 — `tower-defense-game-tilesets`

**Caminho:** `td-tilesets/tower-defense-game-tilesets/PNG/game_background_{N}/`. Cada pasta tem o composto `game_background_{N}.png` + `layers/{layer}.png`.

| N | Tema | Layers |
|---|------|--------|
| 1 | Floresta com rio | `main_bg`, `land`, `bridge`, `fence`, `bush`, `stone`, `tree`, `tree_2`, `river_1`–`6`, `road_1`–`10`, `decor_1`–`5`, `dot` |
| 2 | Lago e pedras | `main_bg`, `land`, `lake`, `stone_1`–`3`, `road_1`–`10`, `decor_1`–`9`, `dot` |
| 3 | Rio com ponte | `main_bg`, `land`, `bridge`, `stone`, `river_1`–`6`, `road_1`–`10`, `decor_1`–`8`, `dot` |
| 4 | Montanhas | `main_bg`, `land`, `mountains`, `stone`, `tree`, `road_1`–`10`, `decor_1`–`3`, `dot` |

Fontes: `AI/` e `EPS/` com `game_background_1`–`4` e `tail_set_1`–`4`.

### Tileset Pack 2 — `tower-defense-game-tile-set-pack-2`

Mesma estrutura, mas os `road_*` ficam em `layers/{N}/road_{1-10}.png`. Os outros layers ficam direto em `layers/`.

| N | Tema | Layers (fora `road_*`) |
|---|------|------------------------|
| 1 | Floresta com lago | `main_bg`, `land`, `lake`, `stone`, `tree_1`, `tree_2`, `bush_1`–`3`, `decor_1`–`5`, `dot` |
| 2 | Lago com pedras | `main_bg`, `land`, `lake_1`–`3`, `stone_1`–`8`, `decor_1`–`7`, `dot` |
| 3 | Rio, ponte e lago | `main_bg`, `land`, `lake`, `bridge`, `river_1`–`6`, `stone_1`, `stone_2`, `tree_1`, `tree_2`, `decor_1`–`6`, `dot` |
| 4 | Árvores e lagos | `main_bg`, `land`, `lake_1`–`3`, `stone_1`–`4`, `tree_1`–`3`, `decor_1`–`3`, `dot` |

Fontes: iguais às do Pack 1.

### Tiled Version — `version-for-the-program-Tiled`

**Caminho:** `td-tilesets/version-for-the-program-Tiled/`

- `PNG/tail_{1-8}/{id}.png`: **todos os tiles são 256×256**, numerados a partir de 1.
- `tailed/tail_{1-8}.tmx`: tileset do Tiled (`tilewidth=256`, mapa de exemplo 100×100). Só confirma a ordem dos ids; não tem nomes semânticos.
- `AI/tail_{1-8}.ai`.

| Tileset | Tema | PNGs | Ids | Base opaca |
|---------|------|-----:|-----|-----------:|
| `tail_1` | grama / vila | 49 | 1–49 | `42` |
| `tail_2` | areia / ruínas | 56 | 1–56 | `21` |
| `tail_3` | pedra escura / runas / pântano ácido | 49 | 1–49 | `26` |
| `tail_4` | neve / gelo | 46 | 1–46 | `35` (alt. `44`, rocha com neve) |
| `tail_5` | selva tropical | 42 | 1–42 | `22` |
| `tail_6` | lava / vulcão | 45 | 1–45 | `24` |
| `tail_7` | pântano cinza / cemitério | 40 | 1–40 | `26` |
| `tail_8` | pântano tóxico / cemitério | 47 | 1–48, **sem `28`** | `34` |

"Base opaca" é o único tile RGB sem alfa do tileset: terreno de preenchimento. A exceção é o `tail_4`, que tem 2 (`35` e `44`).

#### Tiles de caminho `1`–`12`

Conectividade **medida** pelos pixels opacos nas bordas de cada tile. O caminho padrão ocupa a faixa de pixels `43`–`212` do lado.

**`1`–`4` são iguais em todas as famílias:**

| Id | Peça |
|---:|------|
| `1` | curva `S + E` |
| `2` | curva `S + W` |
| `3` | curva `N + E` |
| `4` | curva `N + W` |

**`5`–`8` mudam de ordem conforme a família. Nunca assuma a ordem:**

| Famílias | `5` | `6` | `7` | `8` |
|----------|-----|-----|-----|-----|
| `tail_2`, `tail_5`, `tail_6`, `tail_8` | vertical | horizontal | T `S+W+E` | cruzamento |
| `tail_3` | vertical | horizontal | cruzamento | T `S+W+E` |
| `tail_1` | T `S+W+E` | vertical | cruzamento | horizontal |
| `tail_4`, `tail_7` | T `S+W+E` | cruzamento | vertical | horizontal |

**`9`–`12` não são peças avulsas.** Formam uma **junção larga 2×2** (`9 10` em cima, `11 12` embaixo). As saídas externas ficam na faixa padrão: `W` do 9, `S` do 11 e `E` do 12. É igual em todas as famílias.

Os outros T (`N+S+W`, `N+S+E`, `N+W+E`) não existem como tile. Os `.tmx` de exemplo do autor os obtêm **girando o T** com as flags de flip do Tiled: `HV` = 180°, `HD`/`VD` = 90°. O T é o único tile girado nos 8 exemplos.

**Validação:** a tabela acima foi conferida contra os `.tmx` (layers `road` e `river`, com flips). Deu 0 inconsistências em 1.064 pares de tiles vizinhos nas 8 famílias. Os mapas de exemplo podem ser renderizados com `/Users/dogo/Downloads/Tiled.app/Contents/MacOS/tmxrasterizer -t 40 tailed/tail_N.tmx out.png`. O conteúdo fica num bloco de ~11×9 tiles perto do centro do mapa 100×100.

#### Peças compostas e decoração por família

Peças marcadas como **composta** só fazem sentido juntas. Usadas sozinhas, aparecem cortadas na borda do tile. Notação: `a b / c d` = 2×2 (linha de cima / linha de baixo); `a / b` = empilhado na vertical; `a b` = lado a lado. Todas as compostas abaixo foram confirmadas nos `.tmx` de exemplo: cada vez que um id aparece, os outros pedaços estão na posição indicada.

Em todas as famílias os ids `13`–`18` são o "rio" do tema (água, lava, lodo etc.), com a mesma lógica dos tiles de estrada: `13` curva `S+E`, `14` curva `S+W`, `15` curva `N+E`, `16` curva `N+W`, `17` vertical, `18` horizontal. Exceção: no `tail_2` o rio é `15`–`20` na mesma ordem, e `13 14` é um lago.

**`tail_1` — grama / vila (base `42`)**
| Função | Ids |
|---|---|
| ponte | `27` |
| props isolados | `19` arbusto, `20` placa, `21` toco, `22` mancha de feno, `23` fogueira, `24` pedra, `25` toras, `26` cerca, `28` casa, `29` bandeira, `33` árvore |
| grupos em 1 tile | `30` arbustos, `31` tocos, `32` cercas, `34` pilhas de toras, `35` fogueiras+pedra+arbusto, `36` pedras, `37` 2 árvores (preenche o tile), `47`–`49` pedras/arbustos/tocos |
| composta | `38 39 / 40 41` moinho · `43 44 / 45 46` bosque |

**`tail_2` — areia / ruínas (base `21`)**
| Função | Ids |
|---|---|
| lago (composta) | `13 14` |
| ponte | `54` |
| props isolados | `23` toco, `24` palha seca, `25` fogueira, `26` placa, `27` toras, `28` mancha de terra, `29` cacto, `32` ossada, `33` crânio de boi, `41` e `42` árvores secas, `43` torre de vigia, `55` casa, `56` bandeira |
| grupos em 1 tile | `22` pedras, `30` pedra+cactos, `31` pedras/tocos/cacto, `34` cactos+pedra, `35` cactos, `36` toras, `37` tocos, `38` fogueiras+pedra+cacto, `39` palha, `40` pedras |
| composta | `44 / 45` torre ameiada com casa · `46 47 / 48 49` moinho · `50 51 / 52 53` bosque seco |

**`tail_3` — pedra escura / runas (base `26`)**
| Função | Ids |
|---|---|
| lago ácido (composta) | `19 20` |
| ponte | `21` |
| props isolados | `22` casa, `23` bandeira, `24` toco, `27` placa, `28` fogueira, `29` galhos secos, `31` mancha de terra, `35`–`38` pedras com runa, `41` árvore morta, `47` torre de vigia |
| grupos em 1 tile | `25` rochas, `30` rochas+tocos, `32` fogueiras+rochas, `33` rochas+tocos, `34` tocos, `39` rochas, `40` 2 árvores mortas, `42` galhos secos |
| composta | `43 44 / 45 46` bosque morto · `48 / 49` torre ameiada com casa |

**`tail_4` — neve / gelo (base `35`)**
| Função | Ids |
|---|---|
| lago congelado (composta) | `19 20` |
| ponte | `30` |
| props isolados | `21` torre de vigia, `29` pinheiro, `31` cabana, `32` bandeira, `33` toco, `36` placa, `37` fogueira, `40` mancha de gelo |
| grupos em 1 tile | `28` 2 pinheiros, `34` rochas com neve, `38` rochas com neve, `39` rochas+fogueira, `41` rocha+tocos, `42` tocos, `43` rochas+tocos |
| composta | `22 / 23` torre ameiada com casa · `24 25 / 26 27` bosque de pinheiros · `44` (opaco) + `45`, `46` terreno de rocha com neve e suas bordas |

**`tail_5` — selva tropical (base `22`)**
| Função | Ids |
|---|---|
| lago (composta) | `35 36` |
| ponte | `19` |
| props isolados | `20` cabana de palha, `21` bandeira, `29` mancha de areia, `41` palmeira alta, `42` palmeira |
| grupos em 1 tile | `23`–`28`, `30`–`32` pedras/folhagem/tocos/fogueira/placa |
| composta | `33 34` mancha de lama · `37 38 / 39 40` bosque de palmeiras (as copas passam da borda) |

**`tail_6` — lava / vulcão (base `24`)**
| Função | Ids |
|---|---|
| ponte | `19` |
| props isolados | `21` bandeira, `25` placa, `27` crânio de boi, `28` ossada, `29` mancha de cinza |
| grupos em 1 tile | `20` poças de lava pequenas, `22`, `23` e `26` rochas pontiagudas, `30` rochas, `31` mini vulcões, `32` cascalho |
| composta | `37 / 38` gárgula sobre pilar com runas · `39 40` fosso de lava · `33`–`36` e `41`–`45` bordas e penhascos de um lago de lava (só funcionam montados) |

**`tail_7` — pântano cinza / cemitério (base `26`)**
| Função | Ids |
|---|---|
| poça (composta) | `19 20 / 21 22` |
| ponte | `23` |
| props isolados | `24` cabana, `25` bandeira, `27` crânio de boi, `28` ossada, `30` mancha, `34` placa, `35` e `36` árvores mortas |
| grupos em 1 tile | `29` buracos/pedras, `31` pedras, `32` lápides, `33` lápides+pedras |
| composta | `37 38 / 39 40` bosque morto |

**`tail_8` — pântano tóxico / cemitério (base `34`, sem tile `28`)**
| Função | Ids |
|---|---|
| poças | `19`, `20` isoladas; `21 22` composta |
| névoa (composta) | `23 24 25` faixa horizontal |
| ponte | `26` |
| props isolados | `27` obelisco, `29` bandeira, `35` crânio de boi, `36` ossada, `39` mancha, `42` placa, `43` e `44` árvores do pântano |
| grupos em 1 tile | `37`, `38`, `40` e `41` rochas |
| composta | `30 31 / 32 33` árvore retorcida com corvo e esqueleto · `45 46 / 47 48` bosque do pântano |

Para conferir visualmente: `tools/asset_pipeline/preview_tiles.py` gera `tools/asset_pipeline/_debug/{tail}_sheet.png` para as 8 famílias. `_debug/` está no `.gitignore`.

---

## Formatos de Arquivo

| Extensão | Descrição | Onde aparece |
|----------|-----------|-------------|
| `.png` | Sprites/frames prontos | Todos os packs |
| `.ai` | Adobe Illustrator | Todos os packs |
| `.eps` | EPS vetorial | Todos os packs, exceto a versão Tiled |
| `.fla` | Adobe Flash/Animate | Torres archer, magic e stone |
| `.scml` | Spriter | Packs de monstros e magic-effects |
| `.tmx` | Tiled Map Editor | `td-tilesets/version-for-the-program-Tiled/tailed/` |
| `.txt` | `license.txt` + `readme.txt` (fonte usada) | `TXT/` de cada pack |

---

## Notas Importantes

### Anomalias do kit

1. **Prefixo fixo:** `monster-character-2d-sprites` sempre usa `2_enemies_1_`, e `tower-defense-monster-2d-sprites` sempre usa `1_enemies_1_`. Identifique o monstro pela pasta.
2. **Frames duplicados** na maioria das animações não-ATTACK/DIE (ver [Monstros](#️-frames-duplicados-verificado-por-hash)).
3. **`fire_2`** existe em AI/EPS de magic-effects, sem PNG.
4. **`rain`** começa no frame `001`; os outros efeitos começam em `000`.
5. **Typos de nome no GUI:** `failed/wondow.png`, `levels/btton_empty.png`, `button__facebook.png` (2 underscores), `upgrade/window_.png`. Os numerais de `levels` e `shop` não têm `num_2`.
6. **`tail_8` não tem o tile `28`** (nem o `.tmx` referencia).
7. **Tiles de caminho `5`–`8` mudam de ordem** entre famílias, e `9`–`12` são um bloco 2×2 (ver [Tiled](#tiles-de-caminho-1-12)).

### Padrões de path para importação

```
# Packs 1 e 2 (20 frames, minúsculo, tem idle)
{pack}/PNG/{N}/{N}_enemies_1_{animation}_{frame:03d}.png

# Pack 3 (10 frames, MAIÚSCULO, sem idle)
monster-character-2d-sprites/PNG/{N}/2_enemies_1_{ANIMATION}_{frame:03d}.png

# Pack 4 (10 frames, MAIÚSCULO, sem idle)
tower-defense-monster-2d-sprites/PNG/{N}/1_enemies_1_{ANIMATION}_{frame:03d}.png

# Layer de background (Pack 1)
td-tilesets/tower-defense-game-tilesets/PNG/game_background_{N}/layers/{layer}.png

# Estrada de background (Pack 2)
td-tilesets/tower-defense-game-tile-set-pack-2/PNG/game_background_{N}/layers/{N}/road_{1-10}.png

# Tile do Tiled (256x256)
td-tilesets/version-for-the-program-Tiled/PNG/tail_{F}/{id}.png
```
