// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterOdin",
    products: [
        .library(name: "TreeSitterOdin", targets: ["TreeSitterOdin"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterOdin",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                "src/scanner.c",
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterOdinTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterOdin",
            ],
            path: "bindings/swift/TreeSitterOdinTests"
        )
    ],
    cLanguageStandard: .c11
)
