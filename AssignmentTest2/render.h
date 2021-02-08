#pragma once
#include <Windows.h>
#include <d3d9.h>

class DXRenderer
{
public:
    DXRenderer(void);
    ~DXRenderer(void);
    int Initialise(HWND hwnd, unsigned int width, unsigned int height);
    int Resize(unsigned int width, unsigned int height);
    void Render(void);
private:
    IDirect3DDevice9* d3dDevice;
    IDirect3DSwapChain9* SwapChain;
    unsigned int m_width, m_height;
};