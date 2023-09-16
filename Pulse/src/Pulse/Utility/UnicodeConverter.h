#pragma once

#include <string>

namespace Pulse::Utility {

	// Class to convert Unicode code points to UTF-8
	class UnicodeConverter {
	public:
		
		static std::string ToUTF8(unsigned int codepoint); // Static function to convert a Unicode code point to a UTF-8 string
			
	}; // class UnicodeConverter

} // namespace Pulse::Utility
