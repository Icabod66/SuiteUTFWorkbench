#include <windows.h>

#include <cstdint>

#include "suite_utf.h"

namespace
{
constexpr wchar_t window_class_name[] = L"SuiteUTFWorkbenchWindow";
constexpr wchar_t application_name[] = L"SuiteUTFWorkbench";

bool verify_suite_utf_link() noexcept
{
    constexpr std::uint8_t sample[] = {'H', 'i'};
    std::uint32_t bom_bytes = 0;

    return unicode::utf::identifyUTF(sample, static_cast<std::uint32_t>(sizeof(sample)), bom_bytes)
        == unicode::utf::UTF_TYPE::UTF8;
}

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param) noexcept
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT paint{};
        HDC device_context = BeginPaint(window, &paint);
        constexpr wchar_t greeting[] = L"Hello, World!";
        RECT client_area{};
        GetClientRect(window, &client_area);
        DrawTextW(
            device_context,
            greeting,
            -1,
            &client_area,
            DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        EndPaint(window, &paint);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProcW(window, message, w_param, l_param);
    }
}
} // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int show_command)
{
    if (!verify_suite_utf_link())
    {
        MessageBoxW(nullptr, L"SuiteUTF integration verification failed.", application_name, MB_OK | MB_ICONERROR);
        return 1;
    }

    WNDCLASSEXW window_class{};
    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_procedure;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    window_class.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    window_class.lpszClassName = window_class_name;

    if (RegisterClassExW(&window_class) == 0)
    {
        MessageBoxW(nullptr, L"Unable to register the application window.", application_name, MB_OK | MB_ICONERROR);
        return 1;
    }

    HWND window = CreateWindowExW(
        0,
        window_class_name,
        application_name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        500,
        nullptr,
        nullptr,
        instance,
        nullptr);

    if (window == nullptr)
    {
        MessageBoxW(nullptr, L"Unable to create the application window.", application_name, MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(window, show_command);
    UpdateWindow(window);

    MSG message{};
    BOOL message_result = 0;
    while ((message_result = GetMessageW(&message, nullptr, 0, 0)) != 0)
    {
        if (message_result == -1)
        {
            return 1;
        }

        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    return static_cast<int>(message.wParam);
}
