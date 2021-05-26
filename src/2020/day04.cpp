#include "setup/all.h"

ADVENT_DAY(2020, 4, 237, 172);

namespace
{
    class passport_t
    {
        private:
            enum Field: char { byr, cid, ecl, eyr, hcl, hgt, iyr, pid };
            enum EyeColor: char { amb, blu, brn, gry, grn, hzl, oth };

        public:
            bool is_filled() const
            {
                constexpr uint8_t optional = 0b00000010;
                return (m_filled | optional) == UINT8_MAX;
            }

            bool is_valid() const
            {
                constexpr uint8_t optional = 0b00000010;
                bool is_valid = (m_valid | optional) == UINT8_MAX;

                // printf("pass:\n");
                // print();
                // printf("is valid?\n");
                // printf(" - filled: "); print_bits(m_filled); printf("\n");
                // printf(" - valid: "); print_bits(m_valid); printf("\n");
                // printf(" -> result: %d\n", is_filled() && is_valid);

                return is_filled() && is_valid;
            }

            void set_byr(const sv& sv)
            {
                set_bit(m_filled, Field::byr);
                m_byr = to_int<int>(sv);

                if (1920 <= m_byr && m_byr <= 2002)
                {
                    set_bit(m_valid, Field::byr);
                }
            }

            void set_cid(const sv& sv)
            {
                // NB, this field is ignored, so we don't validate it
                m_cid = sv;
                set_bit(m_filled, Field::cid);
            }

            void set_ecl(const sv& sv)
            {
                set_bit(m_filled, Field::ecl);

                bool valid = true;
                if (sv == "amb") { m_ecl = EyeColor::amb; }
                else if (sv == "blu") { m_ecl = EyeColor::blu; }
                else if (sv == "brn") { m_ecl = EyeColor::brn; }
                else if (sv == "gry") { m_ecl = EyeColor::gry; }
                else if (sv == "grn") { m_ecl = EyeColor::grn; }
                else if (sv == "hzl") { m_ecl = EyeColor::hzl; }
                else if (sv == "oth") { m_ecl = EyeColor::oth; }
                else { valid = false; }

                if (valid)
                    set_bit(m_valid, Field::ecl);
            }

            void set_eyr(const sv& sv)
            {
                set_bit(m_filled, Field::eyr);
                m_eyr = to_int<int>(sv);

                if (2020 <= m_eyr && m_eyr <= 2030)
                {
                    set_bit(m_valid, Field::eyr);
                }
            }

            void set_hcl(const sv& sv)
            {
                set_bit(m_filled, Field::hcl);
                if (sv.size() == 7 && sv[0] == '#')
                {
                    m_hcl = hex_to_dec(sv);

                    if (m_hcl != -1)
                        set_bit(m_valid, Field::hcl);
                }
            }

            void set_hgt(const sv& sv)
            {
                set_bit(m_filled, Field::hgt);

                auto sv_copy = sv;
                if (sv_copy.ends_with("in"))
                {
                    sv_copy.remove_suffix(2);
                    m_hgt = { to_int<int>(sv_copy), false };
                    if (59 <= m_hgt.first && m_hgt.first <= 76)
                        set_bit(m_valid, Field::hgt);
                }
                else if (sv_copy.ends_with("cm"))
                {
                    sv_copy.remove_suffix(2);
                    m_hgt = { to_int<int>(sv_copy), true };
                    if (150 <= m_hgt.first && m_hgt.first <= 193)
                        set_bit(m_valid, Field::hgt);
                }
            }

            void set_iyr(const sv& sv)
            {
                set_bit(m_filled, Field::iyr);
                m_iyr = to_int<int>(sv);

                if (2010 <= m_iyr && m_iyr <= 2020)
                {
                    set_bit(m_valid, Field::iyr);
                }
            }

            void set_pid(const sv& sv)
            {
                set_bit(m_filled, Field::pid);
                m_pid = to_int<int>(sv);

                if (sv.size() == 9 && m_pid != -1)
                    set_bit(m_valid, Field::pid);
            }

        private:
            // State
            uint8_t m_filled = 0;
            uint8_t m_valid = 0;

            // Data
            int m_byr; // Birth Year, uint8_t
            sv m_cid; // Country ID, ignored
            EyeColor m_ecl; // Eye Color
            int m_eyr; // Expiration Year, uint8_t
            int m_hcl; // Hair Color, int, could be replaced by 3 x uint8_t vec?
            std::pair<int, bool> m_hgt; // Height
            int m_iyr; // Issue Year, uint8_t
            int m_pid; // Passport ID, uint32_t
    };
}

output_t Day_2020_4::run_solution(const input_t& input) const
{
    std::vector<passport_t> passports;
    passports.reserve(1000);

    // push first
    passports.push_back(passport_t {});
    size_t pass_idx = 0;

    parse_input(input, [&](const sv& line)
    {
        if (line == "")
        {
            passports.push_back(passport_t {});
            ++pass_idx;
        }
        else
        {
            passport_t& pass = passports[pass_idx];
            const auto& fields = split_multi(line, " ");
            for (const auto& field : fields)
            {
                const auto& keyval = split_multi(field, ":");

                assert(keyval.size() == 2);
                const sv& key = keyval[0];
                const sv& val = keyval[1];

                if (key == "byr") {  pass.set_byr(val);}
                else if (key == "iyr") { pass.set_iyr(val); }
                else if (key == "eyr") { pass.set_eyr(val); }
                else if (key == "hgt") { pass.set_hgt(val); }
                else if (key == "hcl") { pass.set_hcl(val); }
                else if (key == "ecl") { pass.set_ecl(val); }
                else if (key == "pid") { pass.set_pid(val); }
                else if (key == "cid") { pass.set_cid(val); }
                else { assert(false); }
            }
        }
    });

    size_t filled_nb = 0;
    size_t valid_nb = 0;

    for (const auto& pass : passports)
    {
        if (pass.is_filled())
            ++filled_nb;

        if (pass.is_valid())
            ++valid_nb;
    }

    return { filled_nb, valid_nb };
}

void Day_2020_4::run_tests() const
{
    static_assert(hex_to_dec("#000000") == 0);
    static_assert(hex_to_dec("#00000F") == 15);
    static_assert(hex_to_dec("#000010") == 16);
    static_assert(hex_to_dec("#09FBF1") == 654321);
    static_assert(hex_to_dec("#C0FFEE") == 12648430);
}