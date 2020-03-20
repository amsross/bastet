module ArbitraryFloat:
  Ocaml_abstract.Test.ARBITRARY with
    type t = float and type arbitrary('a) = QCheck.arbitrary('a) = {
  type t = float;
  type arbitrary('a) = QCheck.arbitrary('a);

  // These bounds ensure that there are no arithmetic overflows
  let make =
    QCheck.float_range(
      Ocaml_abstract.Float.Bounded.bottom,
      Ocaml_abstract.Float.Bounded.top ** (1. /. 150.),
    );
};

module ApproximatelyEq = {
  type t = float;
  let approx = Printf.sprintf("%.4f");
  let eq = (a, b) => approx(a) == approx(b);
};

module TestFloat =
  Ocaml_abstract.Test.Float(
    ApproximatelyEq,
    AlcotestI.Test,
    QCheckI.Quickcheck,
    ArbitraryFloat,
  );

let suites = TestFloat.suites;
