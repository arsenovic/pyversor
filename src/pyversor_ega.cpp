#include <pyversor/pyversor.h>

namespace pyversor {

namespace ega {

void add_submodule(py::module &m) {
  auto ega = m.def_submodule("ega");
  add_vector(ega);
  add_bivector(ega);
  add_trivector(ega);
  add_rotator(ega);
  add_multivector(ega);
  add_generate(ega);
}

template <typename T>
struct outer_product {
  template <typename A, typename module_t>
  static void add(module_t &m) {
    m.def("outer2", [](const T &lhs, const A &rhs) { return lhs ^ rhs; });
  }

  template <typename A, typename B, typename... Cs, typename module_t>
  static void add(module_t &m) {
    add<A>(m);
    add<B, Cs...>(m);
  }
};

void add_vector(py::module &m) {
  auto t = add_euclidean_multivector<vector_t>(m, "Vector");
  t.def(py::init<double, double, double>());
  t.def("null", &vector_t::null);
  outer_product<vector_t>::add<vector_t, bivector_t>(t);
}

void add_bivector(py::module &m) {
  using vsr::nga::Gen;
  add_euclidean_multivector<bivector_t>(m, "Bivector")
      .def(py::init<double, double, double>())
      .def("__add__",
           [](const bivector_t &a, double b) { return rotator_t(a + b); })
      .def("__radd__",
           [](const bivector_t &a, double b) { return rotator_t(a + b); })
      .def("exp", [](const bivector_t &b) { return Gen::rot(b); });
}

void add_trivector(py::module &m) {
  add_euclidean_multivector<trivector_t>(m, "Trivector")
      .def(py::init<double>());
}

void add_rotator(py::module &m) {
  using vsr::nga::Gen;
  add_euclidean_multivector<rotator_t>(m, "Rotator")
      .def(py::init<double, double, double, double>())
      .def("log", [](const rotator_t &m) { return Gen::log(m); });
}

void add_multivector(py::module &m) {
  add_euclidean_multivector<multivector_t>(m, "Multivector")
      .def(py::init<>())
      .def(py::init<double, double, double, double, double, double, double,
                    double>());
}

void add_generate(py::module &m) {
  using vsr::nga::Gen;
  auto generate = m.def_submodule("generate");
  generate.def("ratio", [](const vector_t &a, const vector_t &b) {
    return vsr::nga::Gen::ratio(a, b);
  });
  generate.def("log", [](const rotator_t &m) { return Gen::log(m); });
  generate.def("exp", [](const bivector_t &b) { return Gen::rot(b); });
}

}  // namespace ega

}  // namespace pyversor