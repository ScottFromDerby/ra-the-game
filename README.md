# texaschainsawdodge

A game written in C for the [WASM-4](https://wasm4.org) fantasy console.


# dev
"w4.exe" watch

# generate asset code
"w4.exe" png2src --c Player.png
"w4.exe" png2src --c Chainsaw.png
"w4.exe" png2src --c FONT_6px.png

# package
"w4.exe" bundle --html testout.html build/cart.wasm


## Links

- [Documentation](https://wasm4.org/docs): Learn more about WASM-4.
- [Snake Tutorial](https://wasm4.org/docs/tutorials/snake/goal): Learn how to build a complete game
  with a step-by-step tutorial.
- [GitHub](https://github.com/aduros/wasm4): Submit an issue or PR. Contributions are welcome!
