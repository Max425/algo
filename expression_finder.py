class ExpressionFinder:
    def __init__(self):
        self.target_total = 200

    def find_expression(self, current_num, expression):
        if current_num == -1:
            if eval(expression) == self.target_total:
                print(f"{expression}={eval(expression)}")
            return

        if expression != '':
            self.find_expression(current_num - 1, f"{expression}+{current_num}")
        self.find_expression(current_num - 1, f"{expression}-{current_num}")
        self.find_expression(current_num - 1, f"{expression}{current_num}")

def main():
    expression_finder = ExpressionFinder()
    expression_finder.find_expression(9, '')

if __name__ == "__main__":
    main()
