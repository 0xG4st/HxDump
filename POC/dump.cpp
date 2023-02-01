#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

const int CHUNK_SIZE = 16;

void hexdump(std::ifstream& in) {

    char buffer[CHUNK_SIZE];
    int i, j;

    while (in.read(buffer, CHUNK_SIZE)) {

        std::cout << std::hex << std::setfill('0') << std::setw(8) << in.tellg() - std::streamoff(0) << "   ";
     
        for (i = 0; i < CHUNK_SIZE; i++) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)(unsigned char)buffer[i] << " ";
            if (i == 7) {
                std::cout << "  ";
            }
        }
        std::cout << "  ";
        for (i = 0; i < CHUNK_SIZE; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                std::cout << buffer[i];
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;

    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string dump_filename = filename + "-dumped.txt";
    std::ofstream out(dump_filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    hexdump(in);

    std::cout.rdbuf(cout_buf);

    in.close();
    out.close();

    return 0;
}
