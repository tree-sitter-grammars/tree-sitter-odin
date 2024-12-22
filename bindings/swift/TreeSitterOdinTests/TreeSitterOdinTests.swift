import XCTest
import SwiftTreeSitter
import TreeSitterOdin

final class TreeSitterOdinTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_odin())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Odin grammar")
    }
}
