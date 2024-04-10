# Changelog

## [1.2.0](https://github.com/tree-sitter-grammars/tree-sitter-odin/compare/v1.1.0...v1.2.0) (2024-04-10)


### Features

* improve indents ([89a372b](https://github.com/tree-sitter-grammars/tree-sitter-odin/commit/89a372b9f1dfa3d510aad20601e71ef4ba446732))
* support the `bit_field` type ([9f2355b](https://github.com/tree-sitter-grammars/tree-sitter-odin/commit/9f2355ba25cc5e2c88ba35eb0d366396935c63a6))

## [1.1.0](https://github.com/amaanq/tree-sitter-odin/compare/v1.0.1...v1.1.0) (2024-01-26)


### Features

* add or_continue and or_break expressions ([d314318](https://github.com/amaanq/tree-sitter-odin/commit/d314318692883fd9858d6a8d1c1aa4fbd849a483))


### Bug Fixes

* bad indenting in `else` and `else if` blocks ([2ed3a06](https://github.com/amaanq/tree-sitter-odin/commit/2ed3a06e80a340d47eed7b4adf8961b4f777ae97))
* commas at the end of a return statement allow for a continuation ([7c8e12d](https://github.com/amaanq/tree-sitter-odin/commit/7c8e12d87810a6a421ebd83e27df369e83ae4c2a))
* parameters with a type annotation can be prefixed with a tag ([07f7192](https://github.com/amaanq/tree-sitter-odin/commit/07f71922d312b90f3c1b7dffb7110637b6bbcc08))
* remove unnecesary tag in unary ops ([78f5fd4](https://github.com/amaanq/tree-sitter-odin/commit/78f5fd496924cd2fc7c48ae0c4b9f992dff90667))
* tag regex ([363c99e](https://github.com/amaanq/tree-sitter-odin/commit/363c99ef938a106b7b8e740d56e56adc09c8816b))
* variable declarations can be procedures ([96a8f1e](https://github.com/amaanq/tree-sitter-odin/commit/96a8f1e57f34206d6305763f0c9f7cafb6354c1d))

## [1.0.1](https://github.com/amaanq/tree-sitter-odin/compare/v1.0.0...v1.0.1) (2023-11-01)


### Bug Fixes

* parsing of separators when blocks are after some newlines ([08f685e](https://github.com/amaanq/tree-sitter-odin/commit/08f685e74864bbcb6a742631f8fe844b0a6dc3e3))

## 1.0.0 (2023-05-13)


### Features

* Initial working parser ([b6f1a70](https://github.com/amaanq/tree-sitter-odin/commit/b6f1a70948666d766cc13e4817cba684823bee56))
