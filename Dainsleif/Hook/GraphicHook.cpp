#include "GraphicHook.h"

#include "../Interfaces/CInterfaceList.h"
#include "../Hacks/Esp.h"
#include "../dllmain.h"

namespace HackFlags
{
    bool bEsp, bLineOverlay, bRectOverlay;
}

extern bool inGame; //decleard in dllmain.cpp

using endScene = HRESULT (__stdcall*) ( IDirect3DDevice9* pDevice );
endScene originalEndScene = nullptr; //An original endscene which is null now.
HWND window = nullptr;
WNDPROC originalWndProc = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT WINAPI WndProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    if ( g_ShowMenu )
    {
        if ( ImGui_ImplWin32_WndProcHandler ( hWnd, msg, wParam, lParam ) )
            return true;
        
        if ( g_csgo.engine->IsActiveApp ( ) )
        {
            switch ( msg )
            {
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_MOUSEHWHEEL:
            case WM_MOUSEACTIVATE:
            case WM_MOVE:
            case WM_MOVING:
            case WM_MOUSEMOVE:
            case WM_NCMOUSEMOVE:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_CHAR:
            case WM_DEADCHAR:
            case WM_SYSCHAR:
            case WM_SYSDEADCHAR:
            case WM_RBUTTONUP:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_LBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MBUTTONDBLCLK:
            case WM_MOUSEWHEEL:
                return 0;

            default: ;
            }
        }
    }
    return CallWindowProc ( originalWndProc, hWnd, msg, wParam, lParam );
}

void InitImGui ( IDirect3DDevice9* pDevice )
{
    IMGUI_CHECKVERSION ( );
    ImGui::CreateContext ( );
    ImGui::CreateContext ( );
    ImGuiIO& io = ImGui::GetIO ( );
    LoadFont ( io );

    ImGui::StyleColorsDark ( );

    ImGui_ImplWin32_Init ( window );
    ImGui_ImplDX9_Init ( pDevice );
}

void ShutdownImGui ( )
{
    ImGui_ImplDX9_Shutdown ( );
    ImGui_ImplWin32_Shutdown ( );
    ImGui::DestroyContext ( );
}

WindowSize GetWindowSize ( )
{
    RECT size;
    WindowSize windowSize{ };
    GetWindowRect ( window, &size );
    windowSize.w = size.right - size.left;
    windowSize.w -= 5; //removing pixels sidebar has.
    windowSize.h = size.bottom - size.top;
    windowSize.h -= 29; //removing pixels topbar has.
    return windowSize;
}

extern std::map< std::string, bool > visibleHacks;

HRESULT __stdcall hookedEndScene ( IDirect3DDevice9* pDevice ) //A function containing a bunch of rendering process, that is gonna be hooked.
{
    static Player* oldLocalPlayer = nullptr;
    Player* localPlayer = Player::GetLocalPlayer ( );
    int gameState = *reinterpret_cast< int* > ( *reinterpret_cast< uintptr_t* > ( Modules::engine + dwClientState ) + dwClientState_State );

    if ( localPlayer != oldLocalPlayer && localPlayer && HackFlags::bEsp )
    {
        std::vector< Player* > playerList = Player::GetAll ( );
        WindowSize ws = GetWindowSize ( );
        Esp esp = Esp ( localPlayer->GetTeam ( ), playerList, *pDevice, ws );
        if ( HackFlags::bLineOverlay )
        {
            esp.LineOverlay ( );
        }

        if ( HackFlags::bRectOverlay )
            esp.RectangleOverlay ( );
    }

    if ( gameState != 6 && inGame )
    {
        oldLocalPlayer = localPlayer;
        inGame = false;
    }


    if ( g_ShowMenu )
    {
        ImGui_ImplDX9_NewFrame ( );
        ImGui_ImplWin32_NewFrame ( );
        ImGui::NewFrame ( );

        LoadTheme ( );

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        ImGui::Begin ( "Dainsleif", &g_ShowMenu, window_flags );

        ShowMenuBar ( visibleHacks ); //tab

        ShowTabMenu ( visibleHacks ); //main view


        ImGui::Separator ( );
        ImGui::Spacing ( );
        ImGui::Spacing ( );
        ImGui::Spacing ( );
        HelpMarker ( "[HACK NOT WORKING?]", "Click \"Update offset\" in the menu bar" );
        ImGui::End ( );

        ImGui::EndFrame ( );
        ImGui::Render ( );
        ImGui_ImplDX9_RenderDrawData ( ImGui::GetDrawData ( ) );
    }
    return originalEndScene ( pDevice );
}

void hookEndScene ( )
{
    auto shaderapidx9 = reinterpret_cast< uintptr_t > ( GetModuleHandle ( "shaderapidx9.dll" ) );
    IDirect3DDevice9* pDevice = *reinterpret_cast< IDirect3DDevice9** > ( shaderapidx9 + dwppDirect3DDevice9 );

    D3DDEVICE_CREATION_PARAMETERS parameters;
    pDevice->GetCreationParameters ( &parameters );

    window = parameters.hFocusWindow;
    originalWndProc = reinterpret_cast< WNDPROC > ( SetWindowLongPtr ( window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR > ( WndProc ) ) );

    InitImGui ( pDevice );

    void** vTable = *reinterpret_cast< void*** > ( pDevice );
    originalEndScene = reinterpret_cast< endScene > ( DetourFunction ( reinterpret_cast< PBYTE > ( vTable[ 42 ] ), reinterpret_cast< PBYTE > ( hookedEndScene ) ) );
}

void unhookEndScene ( )
{
    DetourRemove ( reinterpret_cast< PBYTE > ( originalEndScene ), reinterpret_cast< PBYTE > ( hookedEndScene ) );

    SetWindowLong ( window, GWL_WNDPROC, reinterpret_cast< LONG > ( originalWndProc ) );

    ShutdownImGui ( );
}
