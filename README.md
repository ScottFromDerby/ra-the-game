# ra-the-game

A game written in C for the [WASM-4](https://wasm4.org) fantasy console.

Currently being built using [VS Code](https://code.visualstudio.com/), [TortoiseGit](https://tortoisegit.org/) and [Surge](http://surge.sh/) for deployment.


# dev/build
make clean; make
w4 watch

# generate asset code
```
w4 png2src --c .\FONT_6px.png -t gfxtemplate_h.txt -o src/gfx_font6.h; w4 png2src --c .\FONT_6px.png -t gfxtemplate_c.txt -o src/gfx_font6.c
w4 png2src --c .\FONT_8px.png -t gfxtemplate_h.txt -o src/gfx_font8.h; w4 png2src --c .\FONT_8px.png -t gfxtemplate_c.txt -o src/gfx_font8.c
w4 png2src --c .\SPRITE_AnimTiles.png -t gfxtemplate_h.txt -o src/gfx_animtiles.h; w4 png2src --c .\SPRITE_AnimTiles.png -t gfxtemplate_c.txt -o src/gfx_animtiles.c
w4 png2src --c .\SPRITE_Hud.png -t gfxtemplate_h.txt -o src/gfx_hud.h; w4 png2src --c .\SPRITE_Hud.png -t gfxtemplate_c.txt -o src/gfx_hud.c
w4 png2src --c .\SPRITE_Interiors.png -t gfxtemplate_h.txt -o src/gfx_interiors.h; w4 png2src --c .\SPRITE_Interiors.png -t gfxtemplate_c.txt -o src/gfx_interiors.c
w4 png2src --c .\SPRITE_NPCs.png -t gfxtemplate_h.txt -o src/gfx_npcs.h; w4 png2src --c .\SPRITE_NPCs.png -t gfxtemplate_c.txt -o src/gfx_npcs.c
w4 png2src --c .\SPRITE_Overworld.png -t gfxtemplate_h.txt -o src/gfx_overworld.h; w4 png2src --c .\SPRITE_Overworld.png -t gfxtemplate_c.txt -o src/gfx_overworld.c
w4 png2src --c .\SPRITE_Player.png -t gfxtemplate_h.txt -o src/gfx_player.h; w4 png2src --c .\SPRITE_Player.png -t gfxtemplate_c.txt -o src/gfx_player.c
w4 png2src --c .\SPRITE_Title.png -t gfxtemplate_h.txt -o src/gfx_title.h; w4 png2src --c .\SPRITE_Title.png -t gfxtemplate_c.txt -o src/gfx_title.c
w4 png2src --c .\SPRITE_Weapon.png -t gfxtemplate_h.txt -o src/gfx_weapon.h; w4 png2src --c .\SPRITE_Weapon.png -t gfxtemplate_c.txt -o src/gfx_weapon.c
```

# generate text
```
RATGTextCompressor.exe dialog_input.txt src
```

# package
```
make clean; make
w4 bundle --html testout.html build/cart.wasm
```

## Links

- [Documentation](https://wasm4.org/docs): Learn more about WASM-4.
- [Snake Tutorial](https://wasm4.org/docs/tutorials/snake/goal): Learn how to build a complete game
  with a step-by-step tutorial.
- [GitHub](https://github.com/aduros/wasm4): Submit an issue or PR. Contributions are welcome!
