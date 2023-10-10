

// ÷–¥ µœ÷ memcpy
void* memcpy(void* dest, const void* src, size_t n)
{
    char* cdest = (char*)dest;
    const char* csrc = (const char*)src;
    for (size_t i = 0; i < n; ++i) {
        cdest[i] = csrc[i];
    }
    return dest;
}
