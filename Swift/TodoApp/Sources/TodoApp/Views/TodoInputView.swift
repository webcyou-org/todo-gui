import SwiftUI

struct TodoInputView: View {
    let onSubmit: (String) -> Void

    @State private var text = ""
    @FocusState private var isFocused: Bool

    var body: some View {
        TextField(
            "",
            text: $text,
            prompt: Text("Add Task").foregroundColor(Theme.muted)
        )
        .textFieldStyle(.plain)
        .font(.system(size: 14))
        .foregroundColor(Theme.white)
        .padding(.horizontal, 16)
        .padding(.vertical, 4)
        .frame(height: 35)
        .background(Theme.input)
        .cornerRadius(4)
        .overlay(
            RoundedRectangle(cornerRadius: 4)
                .stroke(isFocused ? Theme.accent : Color.clear, lineWidth: 1)
        )
        .focused($isFocused)
        .onSubmit {
            let trimmed = text.trimmingCharacters(in: .whitespaces)
            guard !trimmed.isEmpty else { return }
            onSubmit(trimmed)
            text = ""
        }
    }
}