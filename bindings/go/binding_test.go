package tree_sitter_odin_test

import (
	"testing"

	tree_sitter "github.com/smacker/go-tree-sitter"
	"github.com/tree-sitter/tree-sitter-odin"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_odin.Language())
	if language == nil {
		t.Errorf("Error loading Odin grammar")
	}
}
