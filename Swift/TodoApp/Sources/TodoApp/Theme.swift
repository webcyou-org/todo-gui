import SwiftUI

enum Theme {
    static let bg        = Color(hex: "1C1C1C")
    static let surface   = Color(hex: "2A2A2A")
    static let input     = Color(hex: "303030")
    static let text      = Color(hex: "D2D2D2")
    static let white     = Color(hex: "FFFFFF")
    static let muted     = Color(hex: "9B9B9B")
    static let accent    = Color(hex: "5DC2AF")
    static let cbBorder  = Color(hex: "D9D9D9")
}

private extension Color {
    init(hex: String) {
        var int: UInt64 = 0
        Scanner(string: hex).scanHexInt64(&int)
        self.init(
            red:   Double((int >> 16) & 0xFF) / 255,
            green: Double((int >>  8) & 0xFF) / 255,
            blue:  Double( int        & 0xFF) / 255
        )
    }
}