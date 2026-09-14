/** Date and month name languages for the page header.
 *
 *  The day and month names are coded using the teletext national option
 *  character subsets defined in ETS 300 706 (Latin G0 national option
 *  sub-sets), so that accented characters can be displayed by the receiver.
 */
#include "datelang.h"

#include <clocale>
#include <cstring>
#include <cctype>

using namespace vbit;

namespace
{
    /* National option character subsets. Only the 13 positions which vary
     * between the subsets are listed (ETS 300 706 Latin G0, 23, 24, 40,
     * 5B to 5F, 60 and 7B to 7E).
     */
    const DateChar mapEnglish[] = {
        {0x00A3, 0x23}, // £
        {0x0024, 0x24}, // $
        {0x2190, 0x5B}, // ←
        {0x00BD, 0x5C}, // ½
        {0x2192, 0x5D}, // →
        {0x2191, 0x5E}, // ↑
        {0x2500, 0x60}, // ─
        {0x00BC, 0x7B}, // ¼
        {0x2016, 0x7C}, // ‖
        {0x00BE, 0x7D}, // ¾
        {0x00F7, 0x7E}, // ÷
    };

    const DateChar mapFrench[] = {
        {0x00E9, 0x23}, // é
        {0x00EF, 0x24}, // ï
        {0x00E0, 0x40}, // à
        {0x00EB, 0x5B}, // ë
        {0x00EA, 0x5C}, // ê
        {0x00F9, 0x5D}, // ù
        {0x00EE, 0x5E}, // î
        {0x00E8, 0x60}, // è
        {0x00E2, 0x7B}, // â
        {0x00F4, 0x7C}, // ô
        {0x00FB, 0x7D}, // û
        {0x00E7, 0x7E}, // ç
    };

    const DateChar mapGerman[] = {
        {0x0024, 0x24}, // $
        {0x00A7, 0x40}, // §
        {0x00C4, 0x5B}, // Ä
        {0x00D6, 0x5C}, // Ö
        {0x00DC, 0x5D}, // Ü
        {0x00B0, 0x60}, // °
        {0x00E4, 0x7B}, // ä
        {0x00F6, 0x7C}, // ö
        {0x00FC, 0x7D}, // ü
        {0x00DF, 0x7E}, // ß
    };

    const DateChar mapItalian[] = {
        {0x00A3, 0x23}, // £
        {0x0024, 0x24}, // $
        {0x00E9, 0x40}, // é
        {0x00B0, 0x5B}, // °
        {0x00E7, 0x5C}, // ç
        {0x00F9, 0x60}, // ù
        {0x00E0, 0x7B}, // à
        {0x00F2, 0x7C}, // ò
        {0x00E8, 0x7D}, // è
        {0x00EC, 0x7E}, // ì
    };

    const DateChar mapCzechSlovak[] = {
        {0x016F, 0x24}, // ů
        {0x010D, 0x40}, // č
        {0x0165, 0x5B}, // ť
        {0x017E, 0x5C}, // ž
        {0x00FD, 0x5D}, // ý
        {0x00ED, 0x5E}, // í
        {0x0159, 0x5F}, // ř
        {0x00E9, 0x60}, // é
        {0x00E1, 0x7B}, // á
        {0x011B, 0x7C}, // ě
        {0x00FA, 0x7D}, // ú
        {0x0161, 0x7E}, // š
    };

    const DateChar mapSwedish[] = { // Swedish/Finnish/Hungarian
        {0x00A4, 0x24}, // ¤
        {0x00C9, 0x40}, // É
        {0x00C4, 0x5B}, // Ä
        {0x00D6, 0x5C}, // Ö
        {0x00C5, 0x5D}, // Å
        {0x00DC, 0x5E}, // Ü
        {0x00E9, 0x60}, // é
        {0x00E4, 0x7B}, // ä
        {0x00F6, 0x7C}, // ö
        {0x00E5, 0x7D}, // å
        {0x00FC, 0x7E}, // ü
    };

    const DateChar mapNordic[] = { // Danish/Norwegian variant of the Nordic set
        {0x00A4, 0x24}, // ¤
        {0x00C9, 0x40}, // É
        {0x00C6, 0x5B}, // Æ
        {0x00D8, 0x5C}, // Ø
        {0x00C5, 0x5D}, // Å
        {0x00DC, 0x5E}, // Ü
        {0x00E9, 0x60}, // é
        {0x00E6, 0x7B}, // æ
        {0x00F8, 0x7C}, // ø
        {0x00E5, 0x7D}, // å
        {0x00FC, 0x7E}, // ü
    };

    const DateChar mapPolish[] = {
        {0x0144, 0x24}, // ń
        {0x0105, 0x40}, // ą
        {0x01B5, 0x5B}, // Ƶ
        {0x015A, 0x5C}, // Ś
        {0x0141, 0x5D}, // Ł
        {0x0107, 0x5E}, // ć
        {0x00F3, 0x5F}, // ó
        {0x0119, 0x60}, // ę
        {0x017C, 0x7B}, // ż
        {0x015B, 0x7C}, // ś
        {0x0142, 0x7D}, // ł
        {0x017A, 0x7E}, // ź
    };

    const DateChar mapPortugueseSpanish[] = {
        {0x00E7, 0x23}, // ç
        {0x0024, 0x24}, // $
        {0x00A1, 0x40}, // ¡
        {0x00E1, 0x5B}, // á
        {0x00E9, 0x5C}, // é
        {0x00ED, 0x5D}, // í
        {0x00F3, 0x5E}, // ó
        {0x00FA, 0x5F}, // ú
        {0x00BF, 0x60}, // ¿
        {0x00FC, 0x7B}, // ü
        {0x00F1, 0x7C}, // ñ
        {0x00E8, 0x7D}, // è
        {0x00E0, 0x7E}, // à
    };

    const DateChar mapTurkish[] = {
        {0x20BA, 0x23}, // ₺
        {0x011F, 0x24}, // ğ
        {0x0130, 0x40}, // İ
        {0x015E, 0x5B}, // Ş
        {0x00D6, 0x5C}, // Ö
        {0x00C7, 0x5D}, // Ç
        {0x00DC, 0x5E}, // Ü
        {0x011E, 0x5F}, // Ğ
        {0x0131, 0x60}, // ı
        {0x015F, 0x7B}, // ş
        {0x00F6, 0x7C}, // ö
        {0x00E7, 0x7D}, // ç
        {0x00FC, 0x7E}, // ü
    };

    const DateChar mapRomanian[] = {
        {0x00A4, 0x24}, // ¤
        {0x021A, 0x40}, // Ț
        {0x0162, 0x40}, // Ţ (older coding of the same letter)
        {0x00C2, 0x5B}, // Â
        {0x0218, 0x5C}, // Ș
        {0x015E, 0x5C}, // Ş
        {0x0102, 0x5D}, // Ă
        {0x00CE, 0x5E}, // Î
        {0x0131, 0x5F}, // ı
        {0x021B, 0x60}, // ț
        {0x0163, 0x60}, // ţ
        {0x00E2, 0x7B}, // â
        {0x0219, 0x7C}, // ș
        {0x015F, 0x7C}, // ş
        {0x0103, 0x7D}, // ă
        {0x00EE, 0x7E}, // î
    };

    const DateChar mapSerbian[] = {
        {0x00CB, 0x24}, // Ë
        {0x010C, 0x40}, // Č
        {0x0106, 0x5B}, // Ć
        {0x017D, 0x5C}, // Ž
        {0x0110, 0x5D}, // Đ
        {0x0160, 0x5E}, // Š
        {0x00EB, 0x5F}, // ë
        {0x010D, 0x60}, // č
        {0x0107, 0x7B}, // ć
        {0x017E, 0x7C}, // ž
        {0x0111, 0x7D}, // đ
        {0x0161, 0x7E}, // š
    };

    /* Languages. Day names are Sunday first and month names January first, to
     * match the order used by strftime(). All are abbreviated to at most three
     * characters. The two character day name substitution uses the first two
     * characters of the same abbreviation.
     */
    const DateLanguage languages[] = {
        { "en", "English", 0, 0, // English
          { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" },
          { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" },
          mapEnglish, sizeof(mapEnglish) / sizeof(DateChar) },
        { "pl", "Polish", 1, 0,
          { "nie", "pon", "wt", "śr", "czw", "pt", "sob" },
          { "sty", "lut", "mar", "kwi", "maj", "cze", "lip", "sie", "wrz", "paź", "lis", "gru" },
          mapPolish, sizeof(mapPolish) / sizeof(DateChar) },
        { "de", "German", 0, 4,
          { "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa" },
          { "Jan", "Feb", "Mär", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" },
          mapGerman, sizeof(mapGerman) / sizeof(DateChar) },
        { "fr", "French", 0, 1,
          { "dim", "lun", "mar", "mer", "jeu", "ven", "sam" },
          { "jan", "fév", "mar", "avr", "mai", "jun", "jul", "aoû", "sep", "oct", "nov", "déc" },
          mapFrench, sizeof(mapFrench) / sizeof(DateChar) },
        { "it", "Italian", 0, 6,
          { "dom", "lun", "mar", "mer", "gio", "ven", "sab" },
          { "gen", "feb", "mar", "apr", "mag", "giu", "lug", "ago", "set", "ott", "nov", "dic" },
          mapItalian, sizeof(mapItalian) / sizeof(DateChar) },
        { "es", "Spanish", 0, 5,
          { "dom", "lun", "mar", "mié", "jue", "vie", "sáb" },
          { "ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic" },
          mapPortugueseSpanish, sizeof(mapPortugueseSpanish) / sizeof(DateChar) },
        { "pt", "Portuguese", 0, 5,
          { "dom", "seg", "ter", "qua", "qui", "sex", "sáb" },
          { "jan", "fev", "mar", "abr", "mai", "jun", "jul", "ago", "set", "out", "nov", "dez" },
          mapPortugueseSpanish, sizeof(mapPortugueseSpanish) / sizeof(DateChar) },
        { "nl", "Dutch", 0, 0,
          { "zo", "ma", "di", "wo", "do", "vr", "za" },
          { "jan", "feb", "mrt", "apr", "mei", "jun", "jul", "aug", "sep", "okt", "nov", "dec" },
          mapEnglish, sizeof(mapEnglish) / sizeof(DateChar) },
        { "no", "Norwegian", 0, 2,
          { "søn", "man", "tir", "ons", "tor", "fre", "lør" },
          { "jan", "feb", "mar", "apr", "mai", "jun", "jul", "aug", "sep", "okt", "nov", "des" },
          mapNordic, sizeof(mapNordic) / sizeof(DateChar) },
        { "sv", "Swedish", 0, 2,
          { "sön", "mån", "tis", "ons", "tors", "fre", "lör" },
          { "jan", "feb", "mar", "apr", "maj", "jun", "jul", "aug", "sep", "okt", "nov", "dec" },
          mapSwedish, sizeof(mapSwedish) / sizeof(DateChar) },
        { "fi", "Finnish", 0, 2,
          { "su", "ma", "ti", "ke", "to", "pe", "la" },
          { "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mar", "jou" },
          mapSwedish, sizeof(mapSwedish) / sizeof(DateChar) },
        { "da", "Danish", 0, 2,
          { "søn", "man", "tir", "ons", "tor", "fre", "lør" },
          { "jan", "feb", "mar", "apr", "maj", "jun", "jul", "aug", "sep", "okt", "nov", "dec" },
          mapNordic, sizeof(mapNordic) / sizeof(DateChar) },
        { "cs", "Czech", 0, 3,
          { "ned", "pon", "úte", "stř", "čtv", "pát", "sob" },
          { "led", "úno", "bře", "dub", "kvě", "čvn", "čvc", "srp", "zář", "říj", "lis", "pro" },
          mapCzechSlovak, sizeof(mapCzechSlovak) / sizeof(DateChar) },
        { "sk", "Slovak", 0, 3,
          { "ned", "pon", "uto", "str", "štv", "pia", "sob" },
          { "jan", "feb", "mar", "apr", "máj", "jún", "júl", "aug", "sep", "okt", "nov", "dec" },
          mapCzechSlovak, sizeof(mapCzechSlovak) / sizeof(DateChar) },
        { "hu", "Hungarian", 0, 2,
          { "vas", "hét", "ked", "sze", "csü", "pén", "szo" },
          { "jan", "feb", "már", "ápr", "máj", "jún", "júl", "aug", "sze", "okt", "nov", "dec" },
          mapSwedish, sizeof(mapSwedish) / sizeof(DateChar) },
        { "ro", "Romanian", 3, 7,
          { "dum", "lun", "mar", "mie", "joi", "vin", "sâm" },
          { "ian", "feb", "mar", "apr", "mai", "iun", "iul", "aug", "sep", "oct", "nov", "dec" },
          mapRomanian, sizeof(mapRomanian) / sizeof(DateChar) },
        { "tr", "Turkish", 3, 3,
          { "paz", "pzt", "sal", "çar", "per", "cum", "cmt" },
          { "oca", "şub", "mar", "nis", "may", "haz", "tem", "ağu", "eyl", "eki", "kas", "ara" },
          mapTurkish, sizeof(mapTurkish) / sizeof(DateChar) },
        { "sr", "Serbian", 3, 5,
          { "ned", "pon", "uto", "sre", "čet", "pet", "sub" },
          { "jan", "feb", "mar", "apr", "maj", "jun", "jul", "avg", "sep", "okt", "nov", "dec" },
          mapSerbian, sizeof(mapSerbian) / sizeof(DateChar) },
    };

    const unsigned int languageCount = sizeof(languages) / sizeof(DateLanguage);

    /** Reverse the three national option bits. Packet X/28/0 carries the option
     *  in the reverse order to the page header control bits, as noted in the
     *  teletext specification.
     */
    uint8_t ReverseOption(uint8_t option)
    {
        return (uint8_t)(((option & 0x01) << 2) | (option & 0x02) | ((option & 0x04) >> 2));
    }

    /** Decode one UTF-8 character
     *  @return number of bytes used, or 1 and the raw byte if it isn't valid UTF-8
     */
    unsigned int Utf8Decode(const char* text, uint32_t* codePoint)
    {
        const uint8_t* s = (const uint8_t*)text;
        if (s[0] < 0x80)
        {
            *codePoint = s[0];
            return 1;
        }
        if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80)
        {
            *codePoint = ((uint32_t)(s[0] & 0x1F) << 6) | (s[1] & 0x3F);
            return 2;
        }
        if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80)
        {
            *codePoint = ((uint32_t)(s[0] & 0x0F) << 12) | ((uint32_t)(s[1] & 0x3F) << 6) | (s[2] & 0x3F);
            return 3;
        }
        *codePoint = s[0]; // not valid UTF-8, treat the byte as the character
        return 1;
    }

    /** Replacements for characters which a national option cannot represent, so
     *  that a name never turns into teletext control codes.
     */
    const DateChar mapAsciiFold[] = {
        {0x00C0, 'A'}, {0x00C1, 'A'}, {0x00C2, 'A'}, {0x00C3, 'A'}, {0x00C4, 'A'}, {0x00C5, 'A'}, {0x00C6, 'A'},
        {0x00C7, 'C'}, {0x00C8, 'E'}, {0x00C9, 'E'}, {0x00CA, 'E'}, {0x00CB, 'E'}, {0x00CC, 'I'}, {0x00CD, 'I'},
        {0x00CE, 'I'}, {0x00CF, 'I'}, {0x00D1, 'N'}, {0x00D2, 'O'}, {0x00D3, 'O'}, {0x00D4, 'O'}, {0x00D5, 'O'},
        {0x00D6, 'O'}, {0x00D8, 'O'}, {0x00D9, 'U'}, {0x00DA, 'U'}, {0x00DB, 'U'}, {0x00DC, 'U'}, {0x00DD, 'Y'},
        {0x00DF, 's'}, {0x00E0, 'a'}, {0x00E1, 'a'}, {0x00E2, 'a'}, {0x00E3, 'a'}, {0x00E4, 'a'}, {0x00E5, 'a'},
        {0x00E6, 'a'}, {0x00E7, 'c'}, {0x00E8, 'e'}, {0x00E9, 'e'}, {0x00EA, 'e'}, {0x00EB, 'e'}, {0x00EC, 'i'},
        {0x00ED, 'i'}, {0x00EE, 'i'}, {0x00EF, 'i'}, {0x00F1, 'n'}, {0x00F2, 'o'}, {0x00F3, 'o'}, {0x00F4, 'o'},
        {0x00F5, 'o'}, {0x00F6, 'o'}, {0x00F8, 'o'}, {0x00F9, 'u'}, {0x00FA, 'u'}, {0x00FB, 'u'}, {0x00FC, 'u'},
        {0x00FD, 'y'}, {0x00FF, 'y'}, {0x0102, 'A'}, {0x0103, 'a'}, {0x0104, 'A'}, {0x0105, 'a'}, {0x0106, 'C'},
        {0x0107, 'c'}, {0x010C, 'C'}, {0x010D, 'c'}, {0x0110, 'D'}, {0x0111, 'd'}, {0x0118, 'E'}, {0x0119, 'e'},
        {0x011A, 'E'}, {0x011B, 'e'}, {0x011E, 'G'}, {0x011F, 'g'}, {0x0130, 'I'}, {0x0131, 'i'}, {0x0139, 'L'},
        {0x013A, 'l'}, {0x013D, 'L'}, {0x013E, 'l'}, {0x0141, 'L'}, {0x0142, 'l'}, {0x0143, 'N'}, {0x0144, 'n'},
        {0x0147, 'N'}, {0x0148, 'n'}, {0x0150, 'O'}, {0x0151, 'o'}, {0x0154, 'R'}, {0x0155, 'r'}, {0x0158, 'R'},
        {0x0159, 'r'}, {0x015A, 'S'}, {0x015B, 's'}, {0x015E, 'S'}, {0x015F, 's'}, {0x0160, 'S'}, {0x0161, 's'},
        {0x0162, 'T'}, {0x0163, 't'}, {0x0164, 'T'}, {0x0165, 't'}, {0x016E, 'U'}, {0x016F, 'u'}, {0x0170, 'U'},
        {0x0171, 'u'}, {0x0178, 'Y'}, {0x0179, 'Z'}, {0x017A, 'z'}, {0x017B, 'Z'}, {0x017C, 'z'}, {0x017D, 'Z'},
        {0x017E, 'z'}, {0x0218, 'S'}, {0x0219, 's'}, {0x021A, 'T'}, {0x021B, 't'},
    };

    const unsigned int asciiFoldCount = sizeof(mapAsciiFold) / sizeof(DateChar);

    /** Convert one Unicode code point into a teletext character. */
    uint8_t EncodeCodePoint(const DateLanguage* lang, uint32_t codePoint)
    {
        if (codePoint < 0x80)
            return (uint8_t)codePoint;

        if (lang != nullptr)
        {
            for (unsigned int i = 0; i < lang->mapSize; i++)
            {
                if (lang->map[i].unicode == codePoint)
                    return lang->map[i].code;
            }
        }

        // not available in this national option, use the plain letter
        for (unsigned int i = 0; i < asciiFoldCount; i++)
        {
            if (mapAsciiFold[i].unicode == codePoint)
                return (uint8_t)mapAsciiFold[i].code;
        }

        return '?';
    }
}

const DateLanguage* vbit::DateLanguageFind(const std::string& code)
{
    for (unsigned int i = 0; i < languageCount; i++)
    {
        if (code == languages[i].code)
            return &languages[i];
    }
    return nullptr;
}

const DateLanguage* vbit::DateLanguageEnglish()
{
    return &languages[0];
}

const DateLanguage* vbit::DateLanguageFromLocale()
{
    // setlocale() gives something like "pl_PL.UTF-8" on Linux or
    // "Polish_Poland.1250" on Windows.
    const char* locale = std::setlocale(LC_TIME, nullptr);
    if (locale == nullptr || strlen(locale) < 2)
        return nullptr;

    // ISO 639-1 style locale name: use the first two letters
    if (isalpha((unsigned char)locale[0]) && isalpha((unsigned char)locale[1]) &&
        (locale[2] == '_' || locale[2] == '-' || locale[2] == '\0'))
    {
        std::string code;
        code += (char)tolower((unsigned char)locale[0]);
        code += (char)tolower((unsigned char)locale[1]);
        const DateLanguage* language = DateLanguageFind(code);
        if (language != nullptr)
            return language;
    }

    // Windows style locale name: match the English language name
    std::string lower;
    for (const char* p = locale; *p != '\0'; p++)
        lower += (char)tolower((unsigned char)*p);

    for (unsigned int i = 0; i < languageCount; i++)
    {
        std::string name;
        for (const char* p = languages[i].name; *p != '\0'; p++)
            name += (char)tolower((unsigned char)*p);
        if (!name.empty() && lower.compare(0, name.size(), name) == 0)
            return &languages[i];
    }

    return nullptr;
}

void vbit::DateLanguageEncode(const DateLanguage* lang, const char* text, uint8_t* out, unsigned int width)
{
    unsigned int written = 0;

    if (text != nullptr)
    {
        const char* p = text;
        while (*p != '\0' && written < width)
        {
            uint32_t codePoint = 0;
            p += Utf8Decode(p, &codePoint);

            if (codePoint < 0x20)
                continue; // skip control codes
            out[written++] = EncodeCodePoint(lang, codePoint);
        }
    }

    while (written < width)
        out[written++] = 0x20;
}

std::string vbit::DateLanguageToTeletext(const DateLanguage* lang, const std::string& text)
{
    std::string result;
    const char* p = text.c_str();

    while (*p != '\0')
    {
        uint32_t codePoint = 0;
        p += Utf8Decode(p, &codePoint);

        if (codePoint < 0x20)
            continue; // skip control codes, including the end of line from the config file
        result += (char)EncodeCodePoint(lang, codePoint);
    }

    return result;
}

uint8_t vbit::DateLanguageOptionBits(const DateLanguage* lang)
{
    if (lang == nullptr)
        return 0;
    return lang->option;
}

uint8_t vbit::DateLanguageCharSetDesignation(const DateLanguage* lang)
{
    if (lang == nullptr)
        return 0;
    // Packet X/28/0 carries the national option bits in the reverse order to
    // the page header control bits.
    return (uint8_t)((lang->region << 3) | ReverseOption(lang->option));
}
