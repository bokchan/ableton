#pragma once

namespace follow_me {

/**
 * @brief      Gets the next delimited token in a string
 *
 * The argument 'pos' is updated with the position from where the next token
 * would begin or std::string::npos if the end of the string has been reached
 *
 * @param[in]  		str    The string
 * @param[in,out]   pos    The position from where to find the token
 * @param[in]  		delim  The delimiter
 *
 * @return     A new constructed string containing the extracted token
 */
std::string get_token(std::string str, size_t &pos, std::string delim = " ");

/**
 * @brief      Trims whitespace from a string from both ends
 *
 * @param[in]  str   The string
 *
 * @return     a copy of the trimmed string
 */
std::string trim(const std::string &str);

} // namespace follow_me
