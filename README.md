# QR Code Generator for y-- (Ymm)

High-quality QR code generation library for y-- powered by Nayuki QR Code Generator.

## Installation

This library is an official external module for the **y--** (**Ymm**) programming language. You can install it effortlessly via **`yenv`**:

```bash
yenv install qrgen
```

This will automatically clone the repository, build the shared library (`liby-qrgen.so` / `y-qrgen.dll`), and register it in `~/.yenv/lib/`.

## Usage

```ymm
import QRgen
from QRgen import *

define function main(): {
    qr = GenerateQRcode("https://github.com/phdgamer0/y---lang", ECC_LEVEL_MEDIUM)
    print("QR Code size: " + string(qr.Size))
}
```

## Documentation

Full documentation, including manual pages and reference texts, are available in the [`docs/`](docs/) directory:
- `qrgen.man`: UNIX troff man page
- `qrgen.txt`: Plaintext documentation reference

You can view the documentation using:
```bash
man -l docs/qrgen.man
```

## License

This project is licensed under the same license as the **y--** programming language. See the [LICENSE](LICENSE) file for details.
