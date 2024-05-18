#include <iostream>
#include <cmath>

std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int getDet(int **matrix, int len_of_matrix) {
    if (len_of_matrix == 1) {
        return matrix[0][0];
    } else if (len_of_matrix == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        int det = 0;

        for (int k = 0; k < len_of_matrix; ++k) {
            int **new_matrix = new int*[len_of_matrix - 1];

            for (int i = 0; i < len_of_matrix - 1; ++i) {
                new_matrix[i] = new int [len_of_matrix - 1];
            }

            for (int i = 1; i < len_of_matrix; ++i) {
                for (int j = 0; j < len_of_matrix; ++j) {
                    if (j == k) {
                        continue;
                    }
                    else if (j < k) {
                        new_matrix[i - 1][j] = matrix[i][j];
                    } else {
                        new_matrix[i - 1][j - 1] = matrix[i][j];
                    }
                }
            }

            det += pow(-1, k + 2) * matrix[0][k] * getDet(new_matrix, len_of_matrix - 1);
        }

        return det;
    }
}


int getByModulo(int num) {
    while (num < 0) {
        num += 26;
    } 

    num = num % alphabet.length();

    return num;
}

int find_nod(int a, int b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }

    return a;
}

int letter_to_key(char letter) {
    for (int i = 0; i < alphabet.length(); ++i) {
        if (letter == alphabet[i]) {
            return i;
        }
    }

    return -1;
}

int divide_by_modulo(int a, int b) {
    while (a % b != 0) {
        a += alphabet.length();
    }

    int num = a / b;

    if (num < 0) {
        return ((num % alphabet.length()) + alphabet.length()) % alphabet.length();
    } 

    return num % alphabet.length();
}

int** find_inverse_matrix(int** matrix, int len_of_matrix, int matrix_det) {
    int **inverse_matrix = new int*[len_of_matrix];

    for (int i = 0; i < len_of_matrix; ++i) {
        inverse_matrix[i] = new int[len_of_matrix];
    }

    for (int k = 0; k < len_of_matrix; ++k) {
        for (int h = 0; h < len_of_matrix; ++h) {
            int **new_matrix = new int*[len_of_matrix];

            for (int i = 0; i < len_of_matrix; ++i) {
                new_matrix[i] = new int[len_of_matrix];
            }

            for (int i = 0; i < len_of_matrix; ++i) {
                for (int j = 0; j < len_of_matrix; ++j) {
                    if (i == k || j == h) {
                        continue;
                    } else if (i < k && j < h) {
                        new_matrix[i][j] = matrix[i][j];
                    } else if (i < k && j > h) {
                        new_matrix[i][j - 1] = matrix[i][j];
                    } else if (i > k && j < h) {
                        new_matrix[i - 1][j] = matrix[i][j];
                    } else {
                        new_matrix[i - 1][j - 1] = matrix[i][j];
                    }
                }
            }

            int det = getDet(new_matrix, len_of_matrix - 1);

            inverse_matrix[k][h] = divide_by_modulo(pow(-1, k + h) * det, matrix_det);
        }
    }

    return inverse_matrix;
}

int main() {
    int len_of_matrix = 0;

    std::cout << "Enter length of the key matrix: ";
    std::cin >> len_of_matrix;

    int **matrix = new int*[len_of_matrix];

    for (int i = 0; i < len_of_matrix; ++i) {
        matrix[i] = new int[len_of_matrix];
    }

    std::cout << "Enter the matrix: ";

    for (int i = 0; i < len_of_matrix; ++i) {
        for (int j = 0; j < len_of_matrix; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int det = getByModulo(getDet(matrix, len_of_matrix));

    while (det == 0) {
        std::cout << "Determinant equals 0. Please enter another matrix: " << '\n';

        for (int i = 0; i < len_of_matrix; ++i) {
            for (int j = 0; j < len_of_matrix; ++j) {
                std::cin >> matrix[i][j];
            }
        }

        det = getDet(matrix, len_of_matrix);
    }

    while (find_nod(alphabet.length(), det) != 1) {
        std::cout << "NOD of Determinant and alphabet length does not equals 1. Please enter another matrix: " << '\n';

        for (int i = 0; i < len_of_matrix; ++i) {
            for (int j = 0; j < len_of_matrix; ++j) {
                std::cin >> matrix[i][j];
            }
        }

        det = getDet(matrix, len_of_matrix);
    }

    for (int i = 0; i < len_of_matrix; ++i) {
        for (int j = 0; j < len_of_matrix; ++j) {
            matrix[i][j] = getByModulo(matrix[i][j]);
        }
    }

    std::string plain_text = "";

    std::cout << "Enter plain text: ";
    std::cin >> plain_text;

    for (auto& c: plain_text) c = toupper(c);

    int left = (len_of_matrix - (plain_text.length() % len_of_matrix));
    int num_of_added = 0;

    for (int i = 0; i < left; ++i) {
        plain_text = plain_text + "A";
        num_of_added += 1;
    }

    int blocks_length = plain_text.length() / len_of_matrix;

    int **blocks = new int*[blocks_length];

    for (int i = 0; i < blocks_length; ++i) {
        blocks[i] = new int[len_of_matrix];
    }

    int block_num = 0;

    for (int i = 0; i < plain_text.length(); ++i) {
        blocks[block_num][i % len_of_matrix] = letter_to_key(plain_text[i]);

        if (i % len_of_matrix == (len_of_matrix - 1)) {
            block_num += 1;
        }
    }

    int sum = 0;

    std::string encoded_string = "";

    for (int i = 0; i < blocks_length; i++) {
        for (int j = 0; j < len_of_matrix; j++) {
            sum = 0;
 
            for (int k = 0; k < len_of_matrix; k++) {
                sum += blocks[i][k] * matrix[k][j];
            }

            encoded_string += alphabet[getByModulo(sum)];
        }
    }

    std::cout << "Encoded string: " << encoded_string << '\n';

    // -------------------------------------------------------------------------------------------------------------
    // DECODING 

    int encoded_blocks_length = encoded_string.length() / len_of_matrix;

    int **encoded_blocks = new int*[encoded_blocks_length];

    for (int i = 0; i < encoded_string.length(); ++i) {
        encoded_blocks[i] = new int[len_of_matrix];
    }

    block_num = 0;
    
    for (int i = 0; i < encoded_string.length(); ++i) {
        encoded_blocks[block_num][i % len_of_matrix] = letter_to_key(encoded_string[i]);

        if (i % len_of_matrix == (len_of_matrix - 1)) {
            block_num += 1;
        }
    }

    int** inverse_matrix = find_inverse_matrix(matrix, len_of_matrix, det);

    int** inverse_matrix_transported = new int*[len_of_matrix];

    for (int i = 0; i < len_of_matrix; ++i) {
        inverse_matrix_transported[i] = new int[len_of_matrix];
    }

    for (int i = 0; i < len_of_matrix; ++i) {
        for (int j = 0; j < len_of_matrix; ++j) {
            inverse_matrix_transported[i][j] = inverse_matrix[j][i];
        }
    }
    
    std::string decoded_string = "";

    for (int i = 0; i < encoded_blocks_length; i++) {
        for (int j = 0; j < len_of_matrix; j++) {
            sum = 0;
 
            for (int k = 0; k < len_of_matrix; k++) {
                sum += encoded_blocks[i][k] * inverse_matrix_transported[k][j];
            }

            decoded_string += alphabet[getByModulo(sum)];
        }
    }

    std::cout << "Decoded text: ";

    for (int i = 0; i < decoded_string.length() - num_of_added; ++i) {
        std::cout << decoded_string[i];
    }

    std::cout << '\n';

    return 0;
}
