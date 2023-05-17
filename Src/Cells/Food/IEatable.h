#pragma once

namespace cells {
	namespace food {
		class IEatable {
		public:
			virtual int getFoodAmount() = 0;
		};
	}
}