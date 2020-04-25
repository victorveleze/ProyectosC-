#include <iostream>
#include <memory>
#include <intrin.h>

std::string getCPUName()
{
    uint32_t data[4] = { 0 };

    _asm
    {
        cpuid;
        mov data[0], ebx;
        mov data[4], edx;
        mov data[8], ecx;
    }

    return std::string((const char*)data);
}

void assembler()
{
    std::cout << "CPU is: " << getCPUName() << std::endl;
    float f1[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    float f2[] = { 5.0f, 4.0f, 3.0f, 2.0f };
    float result[4] = { 0.0f };

    _asm
    {
        movups xmm1, f1;
        movups xmm2, f2;
        mulps xmm1, xmm2;
        movups result, xmm1;
    }

    for (size_t i : result)
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    int32_t d, c;

    _asm
    {
        mov eax, 1;
        cpuid;
        mov d, edx;
        mov c, ecx;
    }

    if ((d & (1 << 26)) != 0)
    {
        std::cout << "SSE2 is supported\n";
    }

    if ((c & 1) != 0)
    {
        std::cout << "SSE3 is supported\n";
    }

    if ((c & (1 << 19)) != 0)
    {
        std::cout << "SSE4.1 is supported\n";
    }

    if ((c & (1 << 20)) != 0)
    {
        std::cout << "SSE4.2 is supported\n";
    }
}

void intrinsics()
{
    auto a = _mm_set_ps(1, 2, 4, 5);
    auto b = _mm_set_ps(5, 3, 4, 6);

    auto c = _mm_add_ps(a, b);

    float res = c.m128_f32[0];

    std::cout << "Res: " << res << std::endl;
}


int main()
{
    intrinsics();
}

