// Generated by CoffeeScript 1.7.1
(function() {
  var AALine, Corridor, Dim, Edge, Pos, Rand, Rect, change_seed, clear, draw_rect, draw_rects, generate_rects, init, inside, intersect, randn, random_int, regenerate, rng, seed, shuffle;

  Rand = (function() {
    function Rand(seed) {
      this.seed = seed;
      this.multiplier = 1664525;
      this.modulo = 4294967296;
      this.offset = 1013904223;
      if (!((this.seed != null) && (0 <= seed && seed < this.modulo))) {
        this.seed = (new Date().valueOf() * new Date().getMilliseconds()) % this.modulo;
      }
    }

    Rand.prototype.seed = function(seed) {
      return this.seed = seed;
    };

    Rand.prototype.randn = function() {
      return this.seed = (this.multiplier * this.seed + this.offset) % this.modulo;
    };

    Rand.prototype.randf = function() {
      return this.randn() / this.modulo;
    };

    Rand.prototype.rand = function(n) {
      return Math.floor(this.randf() * n);
    };

    Rand.prototype.rand2 = function(min, max) {
      return min + this.rand(max - min);
    };

    return Rand;

  })();

  Pos = (function() {
    function Pos(x, y) {
      this.x = x;
      this.y = y;
    }

    Pos.prototype.plus = function(dim) {
      return new Pos(this.x + dim.w, this.y + dim.h);
    };

    Pos.prototype.minus = function(dim) {
      return new Pos(this.x - dim.w, this.y - dim.h);
    };

    return Pos;

  })();

  Dim = (function() {
    function Dim(w, h) {
      this.w = w;
      this.h = h;
    }

    return Dim;

  })();

  AALine = (function() {
    function AALine(p1, p2) {
      var _ref, _ref1;
      this.p1 = p1;
      this.p2 = p2;
      if (this.p1.x === this.p2.x) {
        if (this.p2.y < this.p1.y) {
          _ref = [this.p2, this.p1], this.p1 = _ref[0], this.p2 = _ref[1];
          return;
        }
      }
      if (this.p1.y === this.p2.y) {
        if (this.p2.x < this.p1.x) {
          _ref1 = [this.p2, this.p1], this.p1 = _ref1[0], this.p2 = _ref1[1];
          return;
        }
      }
    }

    return AALine;

  })();

  Edge = (function() {
    function Edge() {}

    Edge.none = -1;

    Edge.right = 0;

    Edge.top = 1;

    Edge.left = 2;

    Edge.bottom = 3;

    return Edge;

  })();

  Rect = (function() {
    Rect.prototype.neighbor = void 0;

    function Rect(pos, dim) {
      this.pos = pos;
      this.dim = dim;
    }

    Rect.prototype.top = function() {
      return new AALine(this.pos, new Pos(this.pos.x + this.dim.w, this.pos.y));
    };

    Rect.prototype.right = function() {
      return new AALine(new Pos(this.pos.x + this.dim.w, this.pos.y), this.pos.plus(this.dim));
    };

    Rect.prototype.bottom = function() {
      return new AALine(new Pos(this.pos.x, this.pos.y + this.dim.h), this.pos.plus(this.dim));
    };

    Rect.prototype.left = function() {
      return new AALine(new Pos(this.pos.x, this.pos.y + this.dim.h), this.pos);
    };

    Rect.prototype.clip = function(other) {
      var last, oldx, oldy;
      last = void 0;
      if (inside(other.pos, this) && inside(other.pos.plus(other.dim), this)) {
        this.dim.w = other.pos.x - 1 - this.pos.x;
        last = Edge.right;
      }
      if (intersect(this.top(), other)) {
        oldy = this.pos.y;
        this.pos.y = other.pos.y + other.dim.h + 1;
        this.dim.h -= this.pos.y - oldy;
        last = Edge.top;
      }
      if (intersect(this.right(), other)) {
        this.dim.w = other.pos.x - 1 - this.pos.x;
        last = Edge.right;
      }
      if (intersect(this.bottom(), other)) {
        this.dim.h = other.pos.y - 1 - this.pos.y;
        last = Edge.bottom;
      }
      if (intersect(this.left(), other)) {
        oldx = this.pos.x;
        this.pos.x = other.pos.x + other.dim.w + 1;
        this.dim.w -= this.pos.x - oldx;
        last = Edge.left;
      }
      return last;
    };

    return Rect;

  })();


  /*
   * a corridor from point 'p1' to point 'p2'
   * with at most one bend in the middle, open at each end to connect rooms
   * 'thickness' wide total, leaving
   * 'inner_thickness' space between sides,
   * following the x or y axis first, respectively
   */

  Corridor = (function() {
    Corridor.prototype._bounds = void 0;

    function Corridor(ctx, tilesize, p1, p2, thickness, inner_thickness) {
      this.ctx = ctx;
      this.tilesize = tilesize;
      this.p1 = p1;
      this.p2 = p2;
      this.thickness = thickness;
      this.inner_thickness = inner_thickness;
      this._bounds = new Rect(new Pos(this.p1.x - Math.floor(this.thickness / 2), this.p1.y - Math.floor(this.thickness / 2)), new Dim(this.p2.x - this.p1.x + this.thickness, this.p2.y - this.p1.y + this.thickness));
    }


    /*
    	 * Helper function to fill a rectangle spanned by two points
    	 * d is the diameter. If the diameter is even, this results
    	 * in an asymmetric shape.
     */

    Corridor.prototype._fill_rect = function(a, b, d, color) {
      var h, w, x1, x2, y1, y2, _ref, _ref1;
      _ref = a.x < b.x ? [a.x, b.x] : [b.x, a.x], x1 = _ref[0], x2 = _ref[1];
      _ref1 = a.y < b.y ? [a.y, b.y] : [b.y, a.y], y1 = _ref1[0], y2 = _ref1[1];
      w = x2 - x1;
      h = y2 - y1;
      this.ctx.fillStyle = color;
      return this.ctx.fillRect(this.tilesize * (x1 - Math.floor(d / 2)), this.tilesize * (y1 - Math.floor(d / 2)), this.tilesize * (w + d), this.tilesize * (h + d));
    };

    Corridor.prototype._set_tile = function(x, y, color) {
      return this._fill_rect(new Pos(x, y), new Pos(x, y), 1, color != null ? color : '#0ff');
    };

    Corridor.prototype.bounds = function() {
      return new Rect(new Pos(this.p1.x - Math.floor(this.thickness / 2), this.p1.y - Math.floor(this.thickness / 2)), new Dim(this.p2.x - this.p1.x + this.thickness, this.p2.y - this.p1.y + this.thickness));
    };

    Corridor.prototype.draw = function(flipped) {
      var close, dir, dir1, dir2, end, mid, sign, start;
      console.log('draw()');
      flipped = flipped != null ? flipped : false;
      start = this.p1;
      mid = void 0;
      if (flipped) {
        mid = new Pos(this.p1.x, this.p2.y);
      } else {
        mid = new Pos(this.p2.x, this.p1.y);
      }
      end = this.p2;
      sign = function(x) {
        if (x < 0) {
          return -1;
        } else if (close(x, 0)) {
          return 0;
        } else {
          return 1;
        }
      };
      close = function(x, y) {
        return Math.abs(x - y) < 0.001;
      };
      if (close(mid.y, start.y)) {
        dir1 = new Dim((Math.floor(this.thickness / 2)) * sign(mid.x - start.x), 0);
      } else {
        dir1 = new Dim(0, (Math.floor(this.thickness / 2)) * sign(mid.y - start.y));
      }
      if (close(mid.y, end.y)) {
        dir2 = new Dim((Math.floor(this.thickness / 2)) * sign(mid.x - end.x), 0);
      } else {
        dir2 = new Dim(0, (Math.floor(this.thickness / 2)) * sign(mid.y - end.y));
      }

      /*
      		 * horizontal or vertical paths without mid have only one rect
      		 * all other paths consist of two rects
      		 * cut off one tile on the side leading into and out of the corridor,
      		 * respectively
       */
      if (close(end.x, start.x) || close(end.y, start.y)) {
        if (close(end.x, start.x)) {
          dir = new Dim(0, (Math.floor(this.thickness / 2)) * sign(end.y - start.y));
        } else {
          dir = new Dim((Math.floor(this.thickness / 2)) * sign(end.x - start.x), 0);
        }
        this._fill_rect(start.plus(dir), end.minus(dir), this.thickness, '#883');
      } else {
        this._fill_rect(start.plus(dir1), mid, this.thickness, '#883');
        this._fill_rect(mid, end.plus(dir2), this.thickness, '#883');
      }
      this._fill_rect(start.plus(dir1), mid, this.inner_thickness, '#000');
      this._fill_rect(mid, end.plus(dir2), this.inner_thickness, '#000');

      /*
      		@_set_tile mid.x, mid.y, '#00f'
       */
      this._set_tile(this.p1.x, this.p1.y, '#000');
      return this._set_tile(this.p2.x, this.p2.y, '#000');
    };

    return Corridor;

  })();

  inside = function(point, rect) {
    return point.x >= rect.pos.x && point.x <= rect.pos.x + rect.dim.w && point.y >= rect.pos.y && point.y <= rect.pos.y + rect.dim.h;
  };

  intersect = function(line, rect) {
    return line.p2.x >= rect.pos.x && line.p2.y >= rect.pos.y && line.p1.x <= rect.pos.x + rect.dim.w && line.p1.y <= rect.pos.y + rect.dim.h;
  };

  random_int = function(a, b) {
    return a + randn() % (b - a + 1);
  };

  shuffle = function(a) {
    var i, j, _i, _ref, _ref1;
    for (i = _i = _ref = a.length - 1; _ref <= 1 ? _i <= 1 : _i >= 1; i = _ref <= 1 ? ++_i : --_i) {
      j = random_int(0, i);
      _ref1 = [a[j], a[i]], a[i] = _ref1[0], a[j] = _ref1[1];
    }
    return a;
  };

  generate_rects = function(ctx, width, height) {
    var corr, e, edge, i, neighbor, other, random_rect, rect, rects, wellformed, x1, x2, xmax, xmin, y1, y2, ymax, ymin, _i, _j, _len;
    random_rect = function(i) {
      var h, w, x, y;
      x = random_int(0, 100 - 3);
      y = random_int(0, 75 - 3);
      w = Math.min(random_int(5, 15 + i), 100 - x);
      h = Math.min(random_int(5, 15 + i), 75 - y);
      return new Rect(new Pos(x, y), new Dim(w, h));
    };
    rects = [random_rect(1)];
    corr = [];
    for (i = _i = 1; _i <= 100; i = ++_i) {
      rect = random_rect(i);
      wellformed = true;
      neighbor = void 0;
      edge = void 0;
      for (_j = 0, _len = rects.length; _j < _len; _j++) {
        other = rects[_j];
        e = rect.clip(other);
        if (e != null) {
          neighbor = other;
          edge = e;
        }
        wellformed = rect.dim.w > 2 && rect.dim.h > 2;
        if (!wellformed) {
          break;
        }
      }
      if (wellformed && neighbor) {
        rect.neighbor = neighbor;
        x1 = void 0;
        y1 = void 0;
        x2 = void 0;
        y2 = void 0;
        if (edge === Edge.top || edge === Edge.bottom) {
          xmin = 1 + Math.max(rect.pos.x, neighbor.pos.x);
          xmax = -2 + Math.min(rect.pos.x + rect.dim.w, neighbor.pos.x + neighbor.dim.w);
          x2 = x1 = random_int(xmin, xmax);
          if (edge === Edge.top) {
            y1 = rect.pos.y - 2;
            y2 = rect.pos.y;
          }
          if (edge === Edge.bottom) {
            y1 = rect.pos.y + rect.dim.h - 1;
            y2 = rect.pos.y + rect.dim.h + 1;
          }
        }
        if (edge === Edge.left || edge === Edge.right) {
          ymin = 1 + Math.max(rect.pos.y, neighbor.pos.y);
          ymax = -2 + Math.min(rect.pos.y + rect.dim.h, neighbor.pos.y + neighbor.dim.h);
          y2 = y1 = random_int(ymin, ymax);
          if (edge === Edge.left) {
            x1 = rect.pos.x - 2;
            x2 = rect.pos.x;
          }
          if (edge === Edge.right) {
            x1 = rect.pos.x + rect.dim.w - 1;
            x2 = rect.pos.x + rect.dim.w + 1;
          }
        }
        corr.push(new Corridor(ctx, 8, new Pos(x1, y1), new Pos(x2, y2), 3, 1));
        rects.push(rect);
      }
    }
    return [rects, corr];
  };

  draw_rect = function(ctx, tilesize, rect, color) {
    ctx.fillStyle = color != null ? color : "#883";
    ctx.fillRect(tilesize * rect.pos.x, tilesize * rect.pos.y, tilesize * rect.dim.w, tilesize * rect.dim.h);
    if (rect.dim.w === 1 || rect.dim.h === 1) {
      return;
    }
    ctx.fillStyle = "#000";
    return ctx.fillRect(tilesize * (rect.pos.x + 1), tilesize * (rect.pos.y + 1), tilesize * (rect.dim.w - 2), tilesize * (rect.dim.h - 2));
  };

  clear = function(ctx, color) {
    ctx.fillStyle = color != null ? color : "#aaa";
    return ctx.fillRect(0, 0, canvas.width, canvas.height);
  };

  draw_rects = function(ctx, tilesize, width, height, rects) {
    var canvas, gridsize, random_color, rect, set_tile, _i, _len, _ref, _results;
    canvas = ctx.canvas;
    gridsize = new Dim(canvas.width / tilesize, canvas.height / tilesize);
    clear(ctx);
    set_tile = function(x, y, color) {
      ctx.fillStyle = color != null ? color : "#883";
      return ctx.fillRect(tilesize * x, tilesize * y, tilesize, tilesize);
    };
    random_color = function() {
      var r;
      r = [random_int(0, 255), 255, 0];
      shuffle(r);
      return "rgb(" + r[0] + "," + r[1] + "," + r[2] + ")";
    };
    draw_rect(ctx, tilesize, rects[0], '#f0f');
    _ref = rects.slice(1);
    _results = [];
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      rect = _ref[_i];
      _results.push(draw_rect(ctx, tilesize, rect, '#883'));
    }
    return _results;
  };

  seed = new Rand().randn();

  rng = new Rand(seed);

  randn = function() {
    return rng.randn();
  };

  change_seed = function(s) {
    seed = s != null ? s : new Rand().randn();
    console.log("seed: " + seed);
    rng = new Rand(seed);
    randn = function() {
      return rng.randn();
    };
    return regenerate();
  };

  init = function() {
    var seed_input;
    seed_input = document.getElementById('seed');
    seed_input.value = seed;
    seed_input.addEventListener('change', function() {
      return change_seed(seed_input.value);
    });
    return regenerate();
  };

  regenerate = function() {
    var c, canvas, corr, ctx, highlight_rect, mouse_pos, rects, redraw, tilesize, _i, _len, _ref, _results;
    canvas = document.getElementById('canvas');
    ctx = canvas.getContext('2d');
    _ref = generate_rects(ctx), rects = _ref[0], corr = _ref[1];
    tilesize = 8;
    mouse_pos = function(event) {
      var rect;
      rect = canvas.getBoundingClientRect();
      return new Pos(Math.floor((event.clientX - rect.left) / tilesize), Math.floor((event.clientY - rect.top) / tilesize));
    };
    highlight_rect = function(event) {
      var c, rect, _i, _j, _len, _len1, _results;
      draw_rects(ctx, tilesize, 800, 600, rects);
      for (_i = 0, _len = rects.length; _i < _len; _i++) {
        rect = rects[_i];
        if (inside(mouse_pos(event), rect)) {
          draw_rect(ctx, tilesize, rect, '#f00');
          if (rect.neighbor) {
            draw_rect(ctx, tilesize, rect.neighbor, '#0f0');
          }
        }
      }
      _results = [];
      for (_j = 0, _len1 = corr.length; _j < _len1; _j++) {
        c = corr[_j];
        _results.push(c.draw());
      }
      return _results;
    };
    redraw = highlight_rect;
    canvas.addEventListener('mousemove', redraw);
    canvas.addEventListener('keydown', redraw);
    draw_rects(ctx, tilesize, 800, 600, rects);
    console.log(corr);
    _results = [];
    for (_i = 0, _len = corr.length; _i < _len; _i++) {
      c = corr[_i];
      _results.push(c.draw());
    }
    return _results;
  };

  window.addEventListener('load', init);

}).call(this);
