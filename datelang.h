#ifndef _DATELANG_H_
#define _DATELANG_H_

#include <cstdint>
#include <string>

/** @brief Languages available for the day and month names in the page header.
 *
 *  Each language names the teletext national option (G0 character set) that the
 *  names are coded in, so that the accented characters are displayed correctly
 *  by the receiver.
 */
namespace vbit
{
    /** A character which is not in the ASCII range, and the teletext character
     *  code used for it in a national option subset.
     */
    struct DateChar
    {
        uint32_t unicode; // Unicode code point
        uint8_t code;     // teletext code for the character
    };

    /** An abbreviated day and month name language. */
    struct DateLanguage
    {
        const char* code;        // ISO 639-1 code used by the date_region option
        const char* name;        // English name, used in log messages
        uint8_t region;          // teletext G0/G2 character set region
        uint8_t option;          // national option index within the region
        const char* days[7];     // abbreviated day names, Sunday first
        const char* months[12];  // abbreviated month names, January first
        const DateChar* map;     // characters used by this language outside ASCII
        unsigned int mapSize;
    };

    /** Find a language by its ISO 639-1 code
     *  @return the language, or nullptr if it is not supported
     */
    const DateLanguage* DateLanguageFind(const std::string& code);

    /** @return the English language, used when nothing else is available */
    const DateLanguage* DateLanguageEnglish();

    /** Work out the language to use from the system locale
     *  @return the language matching the locale, or nullptr if it is not supported
     */
    const DateLanguage* DateLanguageFromLocale();

    /** Encode a name into teletext characters.
     *  Characters which the language cannot represent are replaced by their
     *  unaccented equivalents so that the header stays readable.
     *  @param lang language whose national option characters are used, or nullptr for ASCII
     *  @param text UTF-8 text
     *  @param out receives width teletext characters, padded with spaces
     *  @param width number of characters to write
     */
    void DateLanguageEncode(const DateLanguage* lang, const char* text, uint8_t* out, unsigned int width);

    /** Convert a UTF-8 string into teletext characters, without padding.
     *  Characters which the language cannot represent are replaced by their
     *  unaccented equivalents. Control codes are dropped.
     *  @param lang language whose national option characters are used, or nullptr for ASCII
     *  @param text UTF-8 text
     *  @return the text as teletext characters
     */
    std::string DateLanguageToTeletext(const DateLanguage* lang, const std::string& text);

    /** @return the value for the C12, C13 and C14 national option bits of a language */
    uint8_t DateLanguageOptionBits(const DateLanguage* lang);

    /** @return the 7 bit character set designation used by packet X/28/0 */
    uint8_t DateLanguageCharSetDesignation(const DateLanguage* lang);
}

#endif // _DATELANG_H_
