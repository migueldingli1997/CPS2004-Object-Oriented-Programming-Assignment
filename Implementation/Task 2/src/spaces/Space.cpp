#include "Space.h"
#include "../core/Player.h"

namespace spaces {

    using namespace std;

    Space::Space(const uint id, const string &name) : id(id), name(name) {}

    const uint Space::getId() const {
        return id;
    }

    const std::string Space::getName() const {
        return name;
    }

    bool Space::operator==(const Space &space) const {
        return id == space.id;
    }

    bool Space::operator!=(const Space &space) const {
        return id != space.id;
    }

    ostream &operator<<(ostream &os, const Space &s) {

        os << s.getName();
        return os;
    }

    Space::~Space() {
    }
}