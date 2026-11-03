/* 站点交互：中英切换、算法题筛选与分页、课程展开、站内搜索 */
(function () {
  "use strict";

  var root = document.documentElement;

  /* ---------- 语言 ---------- */
  function readLang() {
    try { return localStorage.getItem("lang") === "en" ? "en" : "zh"; }
    catch (e) { return "zh"; }
  }

  function applyLang(lang) {
    root.setAttribute("data-lang", lang);
    root.setAttribute("lang", lang === "en" ? "en" : "zh-CN");

    var body = document.body;
    var tz = body.getAttribute("data-title-zh");
    var te = body.getAttribute("data-title-en");
    if (tz && te) document.title = lang === "en" ? te : tz;

    document.querySelectorAll(".lang-toggle").forEach(function (btn) {
      btn.setAttribute("aria-pressed", btn.getAttribute("data-lang") === lang ? "true" : "false");
    });

    document.querySelectorAll("input[data-ph-zh]").forEach(function (input) {
      input.setAttribute("placeholder", input.getAttribute(lang === "en" ? "data-ph-en" : "data-ph-zh"));
    });

    document.querySelectorAll("[data-label-zh]").forEach(function (el) {
      var v = el.getAttribute(lang === "en" ? "data-label-en" : "data-label-zh");
      if (v) el.textContent = v;
    });

    try { localStorage.setItem("lang", lang); } catch (e) {}
  }

  var lang = readLang();
  // 支持 ?lang=en / ?lang=zh 直接分享英文或中文版本
  try {
    var qLang = new URLSearchParams(window.location.search).get("lang");
    if (qLang === "en" || qLang === "zh") {
      localStorage.setItem("lang", qLang);
      lang = qLang;
    } else if (!localStorage.getItem("lang") && navigator.language && !/^zh/i.test(navigator.language)) {
      lang = "en";
    }
  } catch (e) {}
  applyLang(lang);

  document.querySelectorAll(".lang-toggle").forEach(function (btn) {
    btn.addEventListener("click", function () {
      applyLang(btn.getAttribute("data-lang") === "en" ? "en" : "zh");
    });
  });

  /* ---------- 课程：全部展开 / 收起 ---------- */
  var expandBtn = document.getElementById("expandAll");
  if (expandBtn) {
    expandBtn.addEventListener("click", function () {
      var open = expandBtn.getAttribute("data-open") !== "1";
      document.querySelectorAll(".topic").forEach(function (d) { d.open = open; });
      expandBtn.setAttribute("data-open", open ? "1" : "0");
      expandBtn.textContent = open ? "收起全部分类" : "展开全部分类";
      expandBtn.setAttribute("data-label-en", open ? "Collapse all" : "Expand all");
    });
  }

  /* ---------- 算法题：筛选 + 分页 ---------- */
  var lcTable = document.getElementById("lcTable");
  if (lcTable) {
    var lcBody = lcTable.tBodies[0];
    var rows = Array.prototype.slice.call(lcBody.rows);
    var pager = document.getElementById("lcPager");
    var chips = Array.prototype.slice.call(document.querySelectorAll("#lcFilters .chip"));
    var size = 10;
    var page = 1;
    var topic = "all";

    function filtered() {
      return rows.filter(function (r) {
        return topic === "all" || r.getAttribute("data-topic") === topic;
      });
    }

    function renderPager(total) {
      var pages = Math.max(1, Math.ceil(total / size));
      if (page > pages) page = pages;
      pager.innerHTML = "";

      var prev = document.createElement("button");
      prev.type = "button";
      prev.textContent = "‹";
      prev.setAttribute("aria-label", "上一页");
      prev.disabled = page === 1;
      prev.addEventListener("click", function () { page -= 1; render(); });
      pager.appendChild(prev);

      for (var i = 1; i <= pages; i++) {
        (function (n) {
          var b = document.createElement("button");
          b.type = "button";
          b.textContent = String(n);
          if (n === page) b.setAttribute("aria-current", "true");
          b.addEventListener("click", function () { page = n; render(); });
          pager.appendChild(b);
        })(i);
      }

      var next = document.createElement("button");
      next.type = "button";
      next.textContent = "›";
      next.setAttribute("aria-label", "下一页");
      next.disabled = page === pages;
      next.addEventListener("click", function () { page += 1; render(); });
      pager.appendChild(next);

      var info = document.createElement("span");
      info.className = "pinfo";
      info.textContent = (document.documentElement.getAttribute("data-lang") === "en")
        ? "Page " + page + " / " + pages + " · " + total + " problems"
        : "第 " + page + " / " + pages + " 页 · 共 " + total + " 题";
      pager.appendChild(info);
    }

    function render() {
      var list = filtered();
      var pages = Math.max(1, Math.ceil(list.length / size));
      if (page > pages) page = pages;
      rows.forEach(function (r) { r.style.display = "none"; });
      list.slice((page - 1) * size, page * size).forEach(function (r) { r.style.display = ""; });
      renderPager(list.length);
    }

    chips.forEach(function (chip) {
      chip.addEventListener("click", function () {
        topic = chip.getAttribute("data-topic");
        page = 1;
        chips.forEach(function (c) {
          c.setAttribute("aria-pressed", c === chip ? "true" : "false");
        });
        render();
      });
    });

    render();

    // 从站内搜索跳转到某一题时，自动切到对应分类与页码
    (function focusFromHash() {
      var h = (window.location.hash || "").replace("#", "");
      if (!h || h.indexOf("lc-") !== 0) return;
      var row = document.getElementById(h);
      if (!row) return;
      topic = row.getAttribute("data-topic");
      page = 1;
      chips.forEach(function (c) {
        c.setAttribute("aria-pressed", c.getAttribute("data-topic") === topic ? "true" : "false");
      });
      render();
      row.scrollIntoView({ block: "center" });
    })();
  }

  /* ---------- 站内搜索 ---------- */
  var searchPage = document.getElementById("searchResults");
  if (searchPage) {
    var input = document.getElementById("q");
    var status = document.getElementById("searchStatus");
    var total = document.getElementById("searchTotal");
    var index = null;
    var state = { q: "", type: "all", page: 1 };
    var pageSize = 12;

    function param(name) {
      return new URLSearchParams(window.location.search).get(name) || "";
    }

    state.q = param("q").trim();
    if (input) input.value = state.q;

    function t(zh, en) {
      var el = document.createElement("span");
      el.className = "lang-zh";
      el.textContent = zh;
      var e2 = document.createElement("span");
      e2.className = "lang-en";
      e2.textContent = en;
      el.appendChild(e2);
      return el;
    }

    function zh(zhText, enText) {
      return document.documentElement.getAttribute("data-lang") === "en" ? enText : zhText;
    }

    function score(item, q) {
      if (!q) return 1;
      var ql = q.toLowerCase();
      var hay = (item.t + " " + (item.te || "") + " " + item.k + " " + (item.d || "") + " " +
        (item.ds || "") + " " + (item.dse || "")).toLowerCase();
      var title = (item.t + " " + (item.te || "")).toLowerCase();
      if (title.indexOf(ql) === 0) return 100;
      if (title.indexOf(ql) > -1) return 60;
      if (hay.indexOf(ql) > -1) return 20;
      return 0;
    }

    function filterType(items) {
      return items.filter(function (i) { return state.type === "all" || i.c === state.type; });
    }

    function render() {
      if (!index) return;
      var items = index.map(function (i) { return { i: i, s: score(i, state.q) }; })
        .filter(function (x) { return x.s > 0 && filterType([x.i]).length; });

      items.sort(function (a, b) { return b.s - a.s || (b.i.u < a.i.u ? 1 : -1); });

      var all = items.map(function (x) { return x.i; });
      var pages = Math.max(1, Math.ceil(all.length / pageSize));
      if (state.page > pages) state.page = pages;

      if (total) {
        total.textContent = state.q
          ? zh("“" + state.q + "” 共 " + all.length + " 条结果", all.length + " result(s) for “" + state.q + "”")
          : zh("共 " + all.length + " 条内容", all.length + " items");
      }

      searchPage.innerHTML = "";
      all.slice((state.page - 1) * pageSize, state.page * pageSize).forEach(function (i) {
        var a = document.createElement("a");
        a.className = "result";
        a.href = i.u;
        a.style.display = "block";

        var ti = document.createElement("div");
        ti.className = "rtitle";
        ti.appendChild(t(i.t, i.te || i.t));
        a.appendChild(ti);

        var meta = document.createElement("div");
        meta.className = "rmeta";
        meta.textContent = (i.d ? i.d + " · " : "") + (i.cn || i.c);
        a.appendChild(meta);

        if (i.ds) {
          var ds = document.createElement("div");
          ds.className = "rdesc";
          ds.appendChild(t(i.ds, i.dse || i.ds));
          a.appendChild(ds);
        }
        searchPage.appendChild(a);
      });

      if (!all.length) {
        var empty = document.createElement("p");
        empty.className = "note";
        empty.style.marginTop = "18px";
        empty.appendChild(t("没有找到相关内容，试试更短的关键词。", "No results. Try a shorter keyword."));
        searchPage.appendChild(empty);
      }

      var old = document.getElementById("searchPager");
      if (old) old.remove();
      if (pages > 1) {
        var pager = document.createElement("div");
        pager.className = "pager";
        pager.id = "searchPager";
        for (var n = 1; n <= pages; n++) {
          (function (num) {
            var b = document.createElement("button");
            b.type = "button";
            b.textContent = String(num);
            if (num === state.page) b.setAttribute("aria-current", "true");
            b.addEventListener("click", function () { state.page = num; render(); });
            pager.appendChild(b);
          })(n);
        }
        searchPage.parentNode.appendChild(pager);
      }
    }

    fetch("assets/data/search.json")
      .then(function (r) { return r.json(); })
      .then(function (data) {
        index = data;
        render();
      })
      .catch(function () {
        if (status) status.textContent = zh("搜索索引加载失败。", "Failed to load the search index.");
      });

    document.querySelectorAll("#searchTypes .chip").forEach(function (chip) {
      chip.addEventListener("click", function () {
        state.type = chip.getAttribute("data-type");
        state.page = 1;
        document.querySelectorAll("#searchTypes .chip").forEach(function (c) {
          c.setAttribute("aria-pressed", c === chip ? "true" : "false");
        });
        render();
      });
    });

    if (input) {
      var form = input.closest("form");
      if (form) {
        form.addEventListener("submit", function (e) {
          e.preventDefault();
          state.q = input.value.trim();
          state.page = 1;
          var url = new URL(window.location.href);
          if (state.q) url.searchParams.set("q", state.q); else url.searchParams.delete("q");
          window.history.replaceState(null, "", url.toString());
          render();
        });
      }
    }
  }
})();
