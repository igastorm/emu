#include <cstddef>
#include <cstdint>
#include <iostream>
using std::cout;

// 1MB
constexpr size_t MEMORY_SIZE = 1024 * 1024;

class Register {
protected:
  // Registers
  enum : uint8_t {
    EAX,
    ECX,
    EDX,
    EBX,
    ESP,
    EBP,
    ESI,
    EDI,
    EIP,
    ELFLAGS,
    REGISTERS_COUNT
  };
};

class Emulator : private Register {
private:
  // Registers
  uint32_t registers[REGISTERS_COUNT];

  // memory
  uint8_t *const memory;

  // Init complete flag
  bool ok;

public:
  Emulator(size_t, uint32_t, uint32_t) noexcept;
  ~Emulator(void) noexcept { delete[] this->memory; }
  bool is_ok(void) const noexcept { return this->ok; };
};

Emulator::Emulator(size_t size, uint32_t eip, uint32_t esp) noexcept
    : registers{}, memory(new(std::nothrow) uint8_t[size]), ok(false) {
  this->registers[ESP] = esp;
  this->registers[EIP] = eip;
  if (this->memory != nullptr) {
    this->ok = true;
  }
}

int main(int argc, char **argv) {
  Emulator emulator(MEMORY_SIZE, 0x0000, 0x7c00);
  cout << "Hello from emu\n";
  return 0;
}
