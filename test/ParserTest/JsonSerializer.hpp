#include <nlohmann/json.hpp>

namespace GMLAST {

class Base;

void to_json(nlohmann::json& j, const Base& base);

}  // namespace GMLAST
