  [@bs.deriving {jsConverter: newType}]
  type bounds = {
    x: int,
    y: int,
    width: int,
    height: int,
  };

  [@bs.send] external getBoundsJs: 'a => abs_bounds = "getBounds";