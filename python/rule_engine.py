#!/usr/bin/env python3
import sys, os, json, psycopg2, pathlib

BASE = pathlib.Path(__file__).resolve().parent
DATA_DIR = BASE.parent / "data"
PG_DSN = os.getenv("PG_DSN", "dbname=inventario user=postgres password=postgres host=localhost")

def get_rule_from_db(context):
    try:
        conn = psycopg2.connect(PG_DSN)
        cur = conn.cursor()
        cur.execute("SELECT regla FROM reglas WHERE contexto = %s", (context,))
        row = cur.fetchone()
        cur.close(); conn.close()
        if row:
            return row[0]
    except Exception as e:
        print(f"[WARN] DB error: {e}", file=sys.stderr)
    return None

def main():
    payload = sys.stdin.read()
    try:
        data = json.loads(payload)
    except Exception:
        data = {"context":"unknown","features":{"coef_var":0.3,"trend":0.0,"units":0}}

    context = data.get("context","unknown")
    f = data.get("features",{})
    rule = get_rule_from_db(context)
    if not rule:
        cv, trend = float(f.get("coef_var", 0.0)), float(f.get("trend", 0.0))
        if cv > 0.60: rule = "DBSCAN"
        elif cv > 0.35 or trend > 0.5: rule = "PARETO_ABC"
        else: rule = "LINEAR_REGRESSION"

    DATA_DIR.mkdir(parents=True, exist_ok=True)
    (DATA_DIR / f"result_{context}.txt").write_text(rule, encoding="utf-8")

if __name__ == "__main__": main()
