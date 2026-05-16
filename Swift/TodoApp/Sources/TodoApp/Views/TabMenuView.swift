import SwiftUI

struct TabMenuView: View {
    @Binding var activeFilter: TabFilter

    var body: some View {
        HStack(spacing: 0) {
            ForEach(TabFilter.allCases, id: \.self) { filter in
                Button(filter.rawValue) {
                    activeFilter = filter
                }
                .buttonStyle(.plain)
                .font(.system(size: 14, weight: activeFilter == filter ? .bold : .regular))
                .foregroundColor(Theme.text)
                .frame(height: 28)
                .padding(.horizontal, 8)
            }
        }
    }
}