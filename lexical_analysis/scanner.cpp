//
// Created by FancyKing on 2020/3/30.
//

#include "scanner.hpp"

bool isInDictionary(const vector<string> &dict, const string &key) {

    for (const auto &itr : dict) {
        if (itr == key) {
            return true;
        }
    }
    return false;
}

bool isIdentifier(const string &str) {

    if (!(isalpha(str[0]) || str[0] == '_'))
        return false;

    for (int i = 1; i < str.length(); i++) {
        if (!(isalnum(str[i]) || str[i] == '_'))
            return false;
    }

    return true;
}

bool isComment(const string &str) {
    return (str == "/*" || str == "//");
}

bool isDigit(const std::string &str) {
    // ref https://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool isString(const std::string &str) {
    return str[0] == '"' && str[str.length() - 1] == '"';
}

bool isBool(const std::string &str) {
    return str == "true" || str == "false";
}

// 文法
bool isLiteral(const std::string &str) {
    return isBool(str) || isString(str) || isDigit(str);
}

// 关键字
bool isKeyword(const std::string &str) {

    // ref https://en.cppreference.com/w/cpp/keyword
    const vector<string> dict{
            "main", "if", "then", "while", "do", "static", "defualt",
            "do", "int", "double", "struct", "break", "else", "long",
            "swtich", "case", "typedf", "char", "return", "const",
            "short", "continue", "for", "void", "sizeof", "#include",
            "unsigned", "float"
    };

    return isInDictionary(dict, str);
}

bool isStatement(const std::string &str) {

    // ref https://en.cppreference.com/w/cpp/language/statements
    const vector<string> dict{
            "for", "while", "switch",
            "continue", "break", "goto",
            "return", "case", "default"
    };

    return isInDictionary(dict, str);
}

bool isOperator(const std::string &str) {

    vector<string> dict{
            "<", ">", "<=", ">=", "*",
            "+", "-", "/", "=", "-=", "*=",
            "+=", "!=", "++", "--", "=="
    };

    return isInDictionary(dict, str);
//    return binary_search(dict.begin(), dict.end(), str);
}

bool isSeparator(const std::string &str) {

    const vector<string> dict{
            "{", "}", ",", "(", ")", ";"
    };

    return isInDictionary(dict, str);
}

bool isNotLegal(const std::string &str) {
    return str == " " || str == "\n";
}

void printPaint(const string &var, const string &token) {

    cout << "(" << mapper.at(var) << ",\t" << token << ")" << endl;
//    cout << "TOKEN : " << token << "\t"
//         << "ID : " << mapper.at(var) << '\t'
//         << "TYPE : " << var << endl;
}

void printRoleOfToken(const string &token) {
    if (isOperator(token)) {
        printPaint("OPERATOR", token);
    } else if (isDigit(token)) {
        printPaint("DIGIT", token);
    } else if (isSeparator(token)) {
        printPaint("SEPARATOR", token);
    } else if (isKeyword(token)) {
        printPaint("KEYWORD", token);
    } else if (isStatement(token)) {
        printPaint("STATEMENT", token);
    } else if (isLiteral(token)) {
        printPaint("LITERAL", token);
    } else if (isIdentifier(token)) {
        printPaint("IDENTIFIER", token);
    } else if (isComment(token)) {
        printPaint("COMMENT", token);
    } else {
        printPaint("NOT_LEGAL", token);
    }
}

void lexicalAnalyze(const string &file_path) {

    string buffer;
    char token;
    bool multi_comment = false, single_comment = false;
    ifstream file;
    // ref http://www.cplusplus.com/reference/fstream/fstream/open/
    // , fstream::in | fstream::binary | fstream::trunc
    file.open(file_path);

    if (!file.is_open()) {
        cout << "[ERROR] Open file failed" << endl;
        exit(0);
    }

//     For Debug flow
//    while (getline(file, buffer)){
//        cout << buffer;
//    }
//    return;
//

    // ref http://www.cplusplus.com/reference/ios/noskipws/?kw=noskipws
    while (file >> noskipws >> token) {

        // 注释跳出检测
        if (single_comment || multi_comment) {

            // 单行注释结束
            if (single_comment && token == '\n') {
                single_comment = false;
            }

            // 多行注释结束
            if (multi_comment && token == '*') {
                file >> token;
                //  */ 形式的多行终结检测
                if (token == EOF) {
                    cout << "[ERROR] Comment multiline" << endl;
                    break;
                }
                if (token == '/') {
                    multi_comment = false;
                }
            }
            // 在注释内部
            continue;
        }

        // 注释跳入检测
        if (token == '/') {
            string pre_comment(1, token);
            file >> token;
            if (token == EOF) {
                printRoleOfToken(pre_comment);
            }

            if (token == '*') {
                // 多行注释开始
                multi_comment = true;
                pre_comment += token;
            } else if (token == '/') {
                // 单行注释开始
                single_comment = true;
                pre_comment += token;
            }

            // 打印注释标号
            if (multi_comment || single_comment) {
                printRoleOfToken(pre_comment);
                continue;
            }
        }

        // 头文件
        if (token == '#') {
            while (file >> noskipws >> token) {
                if (token == '\n') {
                    break;
                }
            }
            string header = "HEADER";
            printPaint(header, "#");
        }

        if (isNotLegal(string(1, token))) {
            if (!buffer.empty()) {
                printRoleOfToken(buffer);
                buffer.clear();
            }
            continue;
        }

        if (isOperator(string(1, token))) {
            if (!buffer.empty() && !isOperator(buffer)) {
                printRoleOfToken(buffer);
                buffer.clear();
            }
        }

        if (isSeparator(string(1, token))) {
            if (!buffer.empty()) {
                printRoleOfToken(buffer);
                buffer.clear();
            }

            if (isSeparator(string(1, token))) {
                printRoleOfToken(string(1, token));
                continue;
            }
        }

        buffer += token;
    }
    file.close();
}