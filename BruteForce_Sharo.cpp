#include <iostream>
#include <chrono>
#include <cmath>

long long guessCount = 0;

bool bruteForce(std::string& attempt, const std::string& charset, const std::string& target, int length, int pos) {
    if (pos == length) {
        guessCount++;
        return attempt == target;
    }
    for (char c : charset) {
        attempt[pos] = c;
        if (bruteForce(attempt, charset, target, length, pos + 1)) return true;
    }
    return false;
}

int main() {
    const std::string CHARSET          = "abcdefghijklmnopqrstuvwxyz";
    const std::string CHARSET_Dig      = "abcdefghijklmnopqrstuvwxyz0123456789";
    const std::string CHARSET_Dig_Caps = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const std::string Password          = "wnvfkt";
    const std::string Password_Dig      = "7j5lt4";
    const std::string Password_Dig_Caps = "J72wTq";

    int option;
    std::string selectedCharset;
    std::string Target;

    std::cout << "Select charset:\n";
    std::cout << "1 - Lowercase only (26)\n";
    std::cout << "2 - Lowercase + digits (36)\n";
    std::cout << "3 - Lowercase + uppercase + digits (62)\n";
    std::cout << "Choice: ";
    std::cin >> option;

    switch (option) {
        case 1:
            selectedCharset = CHARSET;
            Target = Password;
            break;
        case 2:
            selectedCharset = CHARSET_Dig;
            Target = Password_Dig;
            break;
        case 3:
            selectedCharset = CHARSET_Dig_Caps;
            Target = Password_Dig_Caps;
            break;
        default:
            std::cout << "Invalid option.\n";
            return 1;
    }

    std::cout << "Using charset  : " << selectedCharset << "\n";
    std::cout << "Target password: " << Target << "\n";

    int maxLen = Target.length(); 

    std::string attempt;
    bool found = false;
    int foundLen = 0;

    std::cout << "\nCracking..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (int len = 1; len <= maxLen; len++) {
        attempt.assign(len, selectedCharset[0]);
        if (bruteForce(attempt, selectedCharset, Target, len, 0)) {
            found = true;
            foundLen = len;
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ms  = std::chrono::duration<double, std::milli>(end - start).count();
    double sec = ms / 1000.0;

    std::cout << "\n  RESULTS\n";
    std::cout << "--------------------------------------------\n";
    if (found) {
        std::cout << "Password found  : \"" << attempt << "\"\n";
        std::cout << "Password length : " << foundLen << "\n";
    } else {
        std::cout << "Password NOT found.\n";
    }
    std::cout << "Total guesses   : " << guessCount << "\n";
    std::cout << "Time elapsed    : " << ms << " ms";
    if (sec >= 1.0) std::cout << " (" << sec << " sec)";
    std::cout << "\n";
    std::cout << "Guesses/sec     : " << (long long)(guessCount / (sec > 0 ? sec : 0.001)) << "\n";
    std::cout << "============================================\n";

    return 0;
}
