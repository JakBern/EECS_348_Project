#include <stdio.h>
#include <stdlib.h>
#include <cmath>

class OperatorNode : public MathNode{
    public:

        

        virtual FlagType PerformOperation(NumNode &result, const NumNode &lhs, const NumNode &rhs){
            return flags::MathNodeEval::klncorrectArgs;
        }

        virtual FlagType PerformOperation(NumNode &result, const NumNode &operand){
            return flags::MathNodeEval::klncorrectArgs;
        }

    private:
};

class AddNode : public OperatorNode {
    public:
        FlagType PerformOperation(NumNode &result, const NumNode &lhs, const &rhs) override{
            reuslt.value = lhs.value + rhs.value;
            return flags::MathNodeEval::kSuccess;
        }
}

class SubNode : public OperatorNode {
    public:
        FlagType PerformOperation(NumNode &result, const NumNode &lhs, const &rhs) override{
            reuslt.value = lhs.value - rhs.value;
            return flags::MathNodeEval::kSuccess;
        }
}

class MulNode : public OperatorNode {
    public:
        FlagType PerformOperation(NumNode &result, const NumNode &lhs, const &rhs) override{
            reuslt.value = lhs.value * rhs.value;
            return flags::MathNodeEval::kSuccess;
        }
}

class DivNode : public OperatorNode {
    public:
        FlagType PerformOperation(NumNode &result, const NumNode &lhs, const &rhs) override{
            if (rhs.value == 0){
                return flags::MathNodeEval::klncorrectArgs
            }
            reuslt.value = lhs.value / rhs.value;
            return flags::MathNodeEval::kSuccess;
        }
}

class ExpNode : public OperatorNode {
    // Need to look up more information
    public:
        FlagType PerformOperation(NumNode &result, const NumNode &lhs, const &rhs) override{
            result.value = std::pow(lhs.value, rhs.value);
            return flags::MathNodeEval::kSuccess;
        }
}

class SquaredNode : public OperatorNode {
    public:
        FlagType PerformOperation(NumNode &result, const NumNode &operand) override{
            if (operand < 0){
                return flags::MathNodeEval::klncorrectArgs
            }
            result.value = std::sqrt(operand.value);
            return flags::MathNodeEval::kSuccess;
        }
}