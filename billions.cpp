#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>


namespace {

    std::string to_binary(std::uint32_t u, bool spacing = true) {
        static const size_t HEX_BUFFER_SIZE = 9;
        static char hex_buffer[HEX_BUFFER_SIZE];
        memset(hex_buffer, 0, HEX_BUFFER_SIZE);
        snprintf(hex_buffer, HEX_BUFFER_SIZE, "%08X", u);
        static const size_t BIN_BUFFER_SIZE = 37;
        static char bin_buffer[BIN_BUFFER_SIZE];
        int j = 0;
        for (char c : hex_buffer) {
            uint8_t h = 0;
            switch(c) {
                case '0': h = 0u; break;
                case '1': h = 1u; break;
                case '2': h = 2u; break;
                case '3': h = 3u; break;
                case '4': h = 4u; break;
                case '5': h = 5u; break;
                case '6': h = 6u; break;
                case '7': h = 7u; break;
                case '8': h = 8u; break;
                case '9': h = 9u; break;
                case 'A': h = 10u; break;
                case 'B': h = 11u; break;
                case 'C': h = 12u; break;
                case 'D': h = 13u; break;
                case 'E': h = 14u; break;
                case 'F': h = 15u; break;
                case '\0': continue;
            }
            bin_buffer[j++] = h & 0x8 ? '1' : '0';
            bin_buffer[j++] = h & 0x4 ? '1' : '0';
            bin_buffer[j++] = h & 0x2 ? '1' : '0';
            bin_buffer[j++] = h & 0x1 ? '1' : '0';
            if (spacing && (j == 8 || j == 17 || j == 26))
                bin_buffer[j++] = ' ';
        }
        bin_buffer[j] = '\0';
        return std::string(bin_buffer);
    }

    void print_int(std::uint32_t i) {
        std::uint8_t b3 = (i >> 24) & 0xff;
        std::uint8_t b2 = (i >> 16) & 0xff;
        std::uint8_t b1 = (i >> 8) & 0xff;
        std::uint8_t b0 = i & 0xff;
        printf("%10u  %02X %02X %02X %02X  %s\n", i, b3, b2, b1, b0, to_binary(i).c_str());
    }

    typedef union {
        std::uint32_t i;
        std::uint8_t c[];
    } dword;

    struct Memory {
        Memory();
        ~Memory();
    private:
        dword* _ptr;
        static const size_t _n = 100;
        static const size_t _num_bytes = _n * sizeof(*_ptr);
    };

    Memory::Memory() {
        _ptr = (dword*)malloc(_num_bytes);
        if (_ptr == NULL) {
            throw std::runtime_error("Memory not allocated.\n");
        }
        memset(_ptr, 0, _num_bytes);
    };
    Memory::~Memory() {
        free(_ptr);
    }

    struct Sorter {
        void insert(std::uint32_t x);
        void print();
        // std::uint32_t segments[65536] = { 0 };
        std::uint32_t segments[256] = { 0 };
    private:
        Memory _mem;
    };

    void Sorter::insert(std::uint32_t i) {
        print_int(i);
        std::uint16_t hi = (i >> 16) & 0xff;
        if (segments[hi] == 0) {
        }
        // printf("%02X\n", hi);
        printf("%10u\n", segments[hi]);
    }

    void Sorter::print() {
    }

//     // struct L0;
//     // struct L1;
//     // struct L2;
//     // struct L3;

//     // struct L0 {
//     //     L0() {}
//     //     L1 *children = null_memory;
//     // };

//     // struct L1 {
//     //     L1() {}
//     //     L2 *children = null_memory;
//     // };

//     // struct L2 {
//     //     L2() {}
//     //     L3 *children = null_memory;
//     // };

//     // struct L3 {
//     //     L3() {}
//     // };

    std::uint32_t generate_random_number() {
        static std::default_random_engine engine(std::random_device{ }());
        static std::uniform_int_distribution<std::uint32_t> distribution(0, UINT32_MAX);
        return distribution(engine);
    }
} // anonymous namespace

int main(int argc, const char * argv[]) {
    size_t n = 10;
    if (argc > 1)
        n = std::stoul(argv[1]);

    Sorter s;
    for (size_t i = 0; i < n; ++i) {
        s.insert(generate_random_number());
    }

    std::ofstream file("out", std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(s.segments), std::streamsize(sizeof(s.segments)));
        file.close();
    }

    s.print();
    return 0;
}

//     // for (size_t i = 0; i < 10; ++i) {
//     //     std::uint8_t x = _memory[i];
//     //     printf("%02X\n", x);
//     // }

//     // uint32_t* _memory;
//     // _memory = (std::uint32_t*)malloc(num_bytes);
//     // memset(_memory, 0, num_bytes);

//     // // void *memory = std::malloc(1024*1024*1024);

//     //     // Get the elements of the array
//     //     for (size_t i = 0; i < n; ++i) {
//     //         _memory[i] = i;
//     //     }

//     //     // Print the elements of the array
//     //     printf("The elements of the array are: ");
//     //     for (size_t i = 0; i < n; ++i) {
//     //         printf("%u\n", _memory[i]);
//     //         // s.insert(generate_random_number());
//     //     }
//     // }

//     // printf("%z\n", memory);
