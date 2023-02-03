# ra-the-game

A game written in C for the [WASM-4](https://wasm4.org) fantasy console.


# dev/build
w4 watch

# generate asset code
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\FONT_6px.png) | Out-File -Encoding "UTF8" src/gfx_font6.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\FONT_8px.png) | Out-File -Encoding "UTF8" src/gfx_font8.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\SPRITE_Hud.png) | Out-File -Encoding "UTF8" src/gfx_hud.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\SPRITE_PlayerDebug.png) | Out-File -Encoding "UTF8" src/gfx_playerdebug.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\SPRITE_Player.png) | Out-File -Encoding "UTF8" src/gfx_player.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\SPRITE_Overworld.png) | Out-File -Encoding "UTF8" src/gfx_overworld.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\SPRITE_Overworld2.png) | Out-File -Encoding "UTF8" src/gfx_overworld2.h
"#pragma once `n{0}`n{1}`n{2}`n{3}`n{4}`n{5}" -f (w4 png2src --cpp .\SPRITE_NPCs.png) | Out-File -Encoding "UTF8" src/gfx_npcs.h

# package
w4 bundle --html testout.html build/cart.wasm


## Links

- [Documentation](https://wasm4.org/docs): Learn more about WASM-4.
- [Snake Tutorial](https://wasm4.org/docs/tutorials/snake/goal): Learn how to build a complete game
  with a step-by-step tutorial.
- [GitHub](https://github.com/aduros/wasm4): Submit an issue or PR. Contributions are welcome!
