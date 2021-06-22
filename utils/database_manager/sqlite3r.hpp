#include <string>
#include <stdexcept>

namespace sqlit3r {
	template class sqlit3r<typename T> {
		protected:
			std::string path = "";
			std::vector<sqlit3r::tables>;
		public:
			sqlit3r(bool autoclose = true);
			sqlit3r(std::string path, bool autoclose = true);
			void close();
			std::vector<T> get_query();
	};
};
