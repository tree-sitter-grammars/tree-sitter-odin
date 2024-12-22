package tree_sitter_odin_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_odin "tree-sitter-grammars/tree-sitter-odin/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_odin.Language())
	if language == nil {
		t.Errorf("Error loading Odin grammar")
	}
}
