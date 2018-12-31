#include "Comment.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace ast {
            bool Comment::operator==(const Comment& rhs) const {
                return value == rhs.value;
            }

            bool Comment::operator!=(const Comment& rhs) const {
                return !(rhs == *this);
            }

            Comment::Comment(const std::string& raw, const std::string& value) : raw(raw), value(value) {}

            std::string Comment::getValue() {
                return value;
            }

            void Comment::setValue(const std::string& newValue) {
                // '#' is required ahead of non blank comment lines
                if (raw.empty() && !newValue.empty())
                    raw = "#";

                if (value.empty()) {
                    raw += newValue;
                    value = newValue;
                } else {
                    auto pos = raw.find(value);

                    raw.replace(pos, std::string::npos, newValue);
                    value = newValue;
                }
            }

            void Comment::write(std::ostream& output) const {
                output << raw;
            }

            std::ostream& operator<<(std::ostream& os, const Comment& comment) {
                comment.write(os);
                return os;
            }
        }
    }
}