#pragma once
#ifndef CRYPTHOGRAPHY_H
#define CRYPTHOGRAPHY_H

#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

const byte AES_KEY[32] = {
    0x12, 0x3f, 0xa7, 0xc9, 0x7d, 0x4b, 0xe2, 0x8f,
    0x55, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67,
    0x89, 0x0a, 0xbc, 0xde, 0xf0, 0x98, 0x76, 0x54,
    0x32, 0x10, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54
};

inline void encryptToFile(const std::string& plaintext, const std::string& outFile) {
    AutoSeededRandomPool rng;
    byte iv[AES::BLOCKSIZE];
    rng.GenerateBlock(iv, AES::BLOCKSIZE);

    CBC_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(AES_KEY, sizeof(AES_KEY), iv);

    std::string ciphertext;
    StringSource(plaintext, true,
        new StreamTransformationFilter(encryptor,
            new StringSink(ciphertext),
            StreamTransformationFilter::PKCS_PADDING
        )
    );

    // Save IV + ciphertext to file
    std::ofstream out(outFile, std::ios::binary | std::ios::app);
    out.write(reinterpret_cast<const char*>(iv), AES::BLOCKSIZE);
    out.write(ciphertext.data(), ciphertext.size());
    out.close();

    std::cout << "[Encrypt] Saved encrypted data to " << outFile << "\n";
}

inline std::string decryptFromFile(const std::string& inFile) {
    std::ifstream in(inFile, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    // Read IV
    byte iv[AES::BLOCKSIZE];
    in.read(reinterpret_cast<char*>(iv), AES::BLOCKSIZE);
    if (in.gcount() != AES::BLOCKSIZE) {
        throw std::runtime_error("Failed to read IV.");
    }

    // Read ciphertext
    std::string ciphertext((std::istreambuf_iterator<char>(in)), {});
    in.close();

    CBC_Mode<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(AES_KEY, sizeof(AES_KEY), iv);

    std::string recovered;
    StringSource(ciphertext, true,
        new StreamTransformationFilter(decryptor,
            new StringSink(recovered),
            StreamTransformationFilter::PKCS_PADDING
        )
    );

    std::cout << "[Data successfully decrypted]" << "\n";
    return recovered;
}

inline std::string decryptFromString(const std::string& input) {
    if (input.size() < AES::BLOCKSIZE) {
        throw std::runtime_error("Input too small to contain IV and ciphertext.");
    }

    // Extract IV (first 16 bytes)
    const byte* iv = reinterpret_cast<const byte*>(input.data());

    // Extract ciphertext (rest of the input)
    std::string ciphertext = input.substr(AES::BLOCKSIZE);

    // Setup decryptor
    CBC_Mode<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(AES_KEY, sizeof(AES_KEY), iv);

    // Perform decryption
    std::string recovered;
    StringSource(ciphertext, true,
        new StreamTransformationFilter(decryptor,
            new StringSink(recovered),
            StreamTransformationFilter::PKCS_PADDING
        )
    );

    std::cout << "[Data successfully decrypted]" << "\n";
    return recovered;
}

#endif // !1
