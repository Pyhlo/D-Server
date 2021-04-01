#include <iostream>
#include <string>

#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/database.hpp"
#include "mongocxx/instance.hpp"

int main() {
    mongocxx::instance inst{};
    return 0;
}