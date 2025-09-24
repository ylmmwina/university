#include <iostream>
#include <map>

using namespace std;

class EvaluationContext;

class ExpressionNode {
public:
    virtual ~ExpressionNode() {}
    virtual void validate() const = 0;
    virtual double evaluate(const EvaluationContext& context) const = 0;
};

class EvaluationContext {
public:
    map<string, ExpressionNode*> variables;

    void setVariable(const string& name, ExpressionNode* expr) {
        variables[name] = expr;
    }

    ExpressionNode* getVariable(const string& name) const {
        map<string, ExpressionNode*>::const_iterator it = variables.find(name);
        if (it == variables.end()) {
            cerr << "Error: Variable '" << name << "' not defined.\n";
            exit(1);
        }
        return it->second;
    }
};

class ConstantNode : public ExpressionNode {
    double value;
public:
    ConstantNode(double val) : value(val) {}

    void validate() const override {
    }

    double evaluate(const EvaluationContext&) const override {
        return value;
    }
};

class VariableNode : public ExpressionNode {
    string name;
public:
    VariableNode(const string& varName) : name(varName) {}

    void validate() const override {
        if (name.empty() || !isalpha(name[0])) {
            cerr << "Error: Invalid variable name: " << name << "\n";
            exit(1);
        }
    }

    double evaluate(const EvaluationContext& context) const override {
        return context.getVariable(name)->evaluate(context);
    }
};

class OperatorNode : public ExpressionNode {
public:
    enum OperatorType { ADD, SUBTRACT, MULTIPLY, DIVIDE };

private:
    OperatorType op;
    ExpressionNode* left;
    ExpressionNode* right;

public:
    OperatorNode(OperatorType type, ExpressionNode* lhs, ExpressionNode* rhs)
        : op(type), left(lhs), right(rhs) {}

    void validate() const override {
        if (!left || !right) {
            cerr << "Error: Missing operand(s) in operator node.\n";
             exit(1);
        }
        left->validate();
        right->validate();
    }

    double evaluate(const EvaluationContext& context) const override {
        double lhs = left->evaluate(context);
        double rhs = right->evaluate(context);

        switch (op) {
            case ADD:      return lhs + rhs;
            case SUBTRACT: return lhs - rhs;
            case MULTIPLY: return lhs * rhs;
            case DIVIDE:
                if (rhs == 0.0) {
                    cerr << "Error: Division by zero.\n";
                    exit(1);
                }
                return lhs / rhs;
        }

        cerr << "Error: Unknown operator.\n";
        exit(1);
    }
};

int main() {
    EvaluationContext ctx;

    // змінні
    ctx.setVariable("a", new ConstantNode(20));      // a = 20
    ctx.setVariable("b", new ConstantNode(4));       // b = 4

    // вираз 1: додавання: a + b = 24
    ExpressionNode* addExpr = new OperatorNode(
        OperatorNode::ADD,
        new VariableNode("a"),
        new VariableNode("b")
    );

    // вираз 2: віднімання: a - b = 16
    ExpressionNode* subExpr = new OperatorNode(
        OperatorNode::SUBTRACT,
        new VariableNode("a"),
        new VariableNode("b")
    );

    // вираз 3: множення: a * b = 80
    ExpressionNode* mulExpr = new OperatorNode(
        OperatorNode::MULTIPLY,
        new VariableNode("a"),
        new VariableNode("b")
    );

    // вираз 4: ділення: a / b = 5
    ExpressionNode* divExpr = new OperatorNode(
        OperatorNode::DIVIDE,
        new VariableNode("a"),
        new VariableNode("b")
    );

    /*  комплексний вираз: ((a + b) * (a - b)) / (a / b)
        тобто: ((24 * 16) / 5) = 76.8  */
    ExpressionNode* fullExpr = new OperatorNode(
        OperatorNode::DIVIDE,
        new OperatorNode(
            OperatorNode::MULTIPLY,
            addExpr,
            subExpr
        ),
        divExpr
    );

    fullExpr->validate();
    double result = fullExpr->evaluate(ctx);

    std::cout << "Full expression result: " << result << "\n"; // 76.8

    delete ctx.variables["a"];
    delete ctx.variables["b"];
    delete subExpr;
    delete mulExpr;
    delete fullExpr;

    return 0;
}

