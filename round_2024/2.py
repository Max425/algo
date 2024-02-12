from decimal import Decimal, ROUND_DOWN

tests_count = int(input())
for _ in range(tests_count):
    n, p = map(Decimal, input().split())
    res = Decimal(0)
    for _ in range(int(n)):
        a = Decimal(input())
        ko = a * (p / Decimal(100))
        k = ko.quantize(Decimal('0.00'), rounding=ROUND_DOWN)
        k_err = ko.to_integral_value(rounding=ROUND_DOWN)
        res += k - k_err
    print("%.2f" % res)