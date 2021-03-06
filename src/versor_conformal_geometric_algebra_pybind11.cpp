#include <pyversor/pyversor.h>

namespace vsr {

  namespace python {

    namespace py = pybind11;
    using namespace vsr::cga;

    using CGA = vsr::Multivector<
      vsr::algebra<vsr::metric<4, 1, true>, double>,
      vsr::Basis<(short)0, (short)1, (short)2, (short)4, (short)8, (short)16,
                 (short)3, (short)5, (short)6, (short)9, (short)10, (short)12,
                 (short)17, (short)18, (short)20, (short)24, (short)7, (short)11,
                 (short)13, (short)14, (short)19, (short)21, (short)22, (short)25,
                 (short)26, (short)28, (short)15, (short)23, (short)27, (short)29,
                 (short)30, (short)31>>;

    void AddCGA(py::module &m) {
      py::class_<CGA>(m, "CGA", py::buffer_protocol())
        .def(py::init<double, double, double, double, double, double, double,
             double, double, double, double, double, double, double,
             double, double, double, double, double, double, double,
             double, double, double, double, double, double, double,
             double, double, double, double>())
        .def("__init__",
             [](CGA &instance, Vec &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Biv &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Tri &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Rot &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Mot &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Dll &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Lin &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Dlp &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Pln &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Cir &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Par &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Pnt &arg) { new (&instance) CGA(arg); })
        .def("__init__",
             [](CGA &instance, Sph &arg) { new (&instance) CGA(arg); })
        .def("__getitem__", [](CGA &arg, int idx){return arg[idx];})
        .def("__setitem__", [](CGA &arg, int idx, double val) { arg[idx] = val; })
        .def("norm", &CGA::norm)
        .def("rnorm", &CGA::rnorm)
        .def("unit", &CGA::unit)
        .def("rev", [](CGA &arg){return ~arg;})
        .def("inv", [](CGA &arg){return !arg;})
        .def("dual", &CGA::dual)
        .def("undual", &CGA::undual)
        .def("duale", &CGA::duale)
        .def("unduale", &CGA::unduale)
        .def("comm",
             [](const CGA &lhs, const CGA &rhs) {
               return CGA(lhs * rhs - rhs * lhs) * 0.5;
             })
        .def("acomm",
             [](const CGA &lhs, const CGA &rhs) {
               return CGA(lhs * rhs + rhs * lhs) * 0.5;
             })
        .def("mot", [](const CGA &lhs){return Mot(lhs); })
        .def("cir", [](const CGA &lhs){return Cir(lhs); })
        .def("__add__",
             [](const CGA &lhs, const CGA &rhs) { return CGA(lhs + rhs); })
        .def("__sub__",
             [](const CGA &lhs, const CGA &rhs) { return CGA(lhs - rhs); })
        .def("__mul__",
             [](const CGA &lhs, const CGA &rhs) { return (lhs * rhs); })
        .def("__le__",
             [](const CGA &lhs, const CGA &rhs) { return CGA(lhs <= rhs); })
        .def("__xor__",
             [](const CGA &lhs, const CGA &rhs) { return CGA(lhs ^ rhs); })
        .def("spin", (CGA (CGA::*)(const CGA &) const) & CGA::spin)
        .def("__repr__",
             [](const CGA &arg) {
               std::stringstream ss;
               ss.precision(2);
               ss << "CGA: [";
               for (int i = 0; i < arg.Num; ++i) {
                 ss << " " << arg[i];
               }
               ss << " ]";
               return ss.str();
             })
        .def_buffer([](CGA &arg) -> py::buffer_info {
            return py::buffer_info(
                                   &arg.val[0], sizeof(double), py::format_descriptor<double>::format(),
                                   1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
          });
    }

  } // namespace python

} // namespace vsr
