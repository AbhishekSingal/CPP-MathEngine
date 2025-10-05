//
// Created by Abhishek Singal on 09/07/25.
//

#include <Core/ExpressionEvaluater.h>

#include <Core/Utils.h>

namespace MathEngine
{
namespace Core {
    //Helper fucntion to compare operator precedence
    bool compareOperators(char op1 , char op2)
    {
        if(op1 == '^') {return true;}
        else if(op1 == '/'){return op2 == '^' || op2 == '/' ? false : true; }
        else if(op1 == '*'){return op2 == '^' || op2 == '/' || op2 == '*' ? false : true; }
        else if(op1 == '+' || op1 == '-'){return op2 == '^' || op2 == '/' || op2 == '*' || op2 == '+' || op2 == '-' ? false : true; }
        else throw std::exception();
    }

    //Check if char is an operator
    bool ExpressionEvaluater::isOperator(char c)
    {
        return (c == '^' || c == '/' || c== '*' || c == '+' || c== '-') ? true : false;
    }

    //Create the Infix Expression Array
    void ExpressionEvaluater::createInfixArray()
    {
        this->infixArr.clear();

        //Intiliaze iterator , size and char
        int i = 0;
        char c;

        //This will store each item and will be emptied after operator is scanned
        std::string item = "";

        while( i < expression.length() )
        {
            c = expression[i];
            std::string sub_exp = "";

            //Handle Parenthesis
            //In-Place Evaluation
            if (c == '(') {
                int counter = 1;
                i += 1;
                while(counter != 0) {
                    char _c = expression[i];
                    if (_c == '(') {
                        counter++;
                        sub_exp += _c;
                    }else if (_c == ')') {
                        counter--;
                        if (counter != 0) {
                            sub_exp += _c;
                        }
                    }else {
                        sub_exp += _c;
                    }
                    i++;
                }

                ExpressionEvaluater sub_evaluator;
                Rational sub_value = sub_evaluator.evaluateArithmetic(sub_exp);
                if (item == "-" && sub_value < 0) {
                    item = Utils::GetRationalString(-sub_value,1e17);
                }else {
                    item += Utils::GetRationalString(sub_value,1e17);
                }



                if (i == expression.length()) {
                    infixArr.push_back(item);
                }else {
                    continue;
                }
            }

            //If char is operator then pushback the item , empty it and then pushback the operator
            if(isOperator(c))
            {
                if(item != "" && item != "-") { infixArr.push_back(item); item = ""; }

                //Handling minus sign
                //Minus will be added to the item , and the operator will be '+' then
                //Example 5-4 will be written in the array as '5' , '+' , '-4'
                if(c != '-')
                {
                    infixArr.push_back(std::string(1,c));
                }
                //Handle '-' at the start of the expression
                else if(c == '-' && i == 0)
                {
                    item += "-";
                }
                else{
                    //Check if the last item in the array is an operator
                    //If yes , dont pushback '+'
                    if(!isOperator(infixArr[infixArr.size()-1][0])){infixArr.push_back("+");};
                    if(item != "-") { item += "-" ;}
                    else{item = "";}
                }


            }
            //Handle whitespaces
            else if(c != ' '){
                item += c;
            }
            i++;

            //If end of expression reached pushback the last item
            if(i == expression.length()) infixArr.push_back(item);

        }
    }

    //Create the Postfix Array from Infix Array
    void ExpressionEvaluater::createPostFixArray()
    {
        if (this->infixArr.size() == 0)
            return ;
        //Stack to store operators
        std::stack<char> operatorStack;


        //Loop through the infixArr
        for( int i = 0 ; i < infixArr.size() ; i++ )
        {
            std::string item = infixArr[i];

            //If item is operator
            if(isOperator(item[0]) && item.size() == 1)
            {
                char op = item[0];

                //Push the operator if stack is empty
                if(operatorStack.empty()){operatorStack.push(op);}
                else{
                    //If operator in stack has less precedence than scanned operator , push it
                    if(compareOperators(op, operatorStack.top())) {operatorStack.push(op);}

                    //Else keep popping operators from the stack until it is empty or has operator with lesser precedence
                    else{
                        while(!compareOperators(op, operatorStack.top()))
                        {
                            postfixArr.push_back(std::string(1,operatorStack.top()));
                            operatorStack.pop();
                            if(operatorStack.empty()) break;
                        }

                        operatorStack.push(op);
                    }
                }
            }
            //If not operator , push it in the postfixArr
            else{
                postfixArr.push_back(item);
            }
        }

        //Push any remaining operators in the postfixArr
        while(!operatorStack.empty())
        {
            postfixArr.push_back(std::string(1,operatorStack.top()));
            operatorStack.pop();
        }
    }


    //Evaluate the Postfix Array
    void ExpressionEvaluater::evaluatePostfixArray()
    {
        if (this->postfixArr.size() == 0)
            return;
        //Store the value
        std::stack<Rational> values;

        //Loop through the postfixArr
        for(int i = 0 ; i < postfixArr.size() ; i++)
        {
            std::string item = postfixArr[i];

            //If item is operator , pop last two values and apply the operator then pushback the value after applying the operator
            if(isOperator(item[0]) && item.size() == 1)
            {
                Rational num1 = values.top() ; values.pop() ;
                Rational num2 = values.top() ; values.pop() ;
                Rational num;

                if(item == "^") {num = std::pow(num2 , num1);}
                else if(item == "/"){num = num2/num1;}
                else if(item == "*"){num = num2*num1;}
                else if(item == "+"){num = num2+num1;}

                values.push(num);
            }
            //Else push the item
            else{
                values.push(std::stold(item));

            }
        }

        //Return the value remaining in the stack
        value = values.top();
    }




    //Evaluate Standard Arithmetic Expressions
    Rational ExpressionEvaluater::evaluateArithmetic(std::string expression) {
        this->expression = expression;
        createInfixArray();
        createPostFixArray();
        evaluatePostfixArray();
        return value;
    }

    Rational ExpressionEvaluater::evaluateExpression(std::string exprssion) {
        this->expression = exprssion;

        std::vector<std::string> constants = {"PI","e"};
        std::vector<std::string> functions = {"arcsin","arccos","arctan","cosec","sec","sin","cos","tan","cot","ln","mod","sqrt"};

        std::string og_exp = expression;

        //Resolve Constants
        for (std::string s : constants) {
            std::string t_expression = "";
            for (int i = 0 ; i < expression.length() ; i++) {
                if (expression.substr(i,s.length()) == s) {
                    if (s == "PI") {
                        t_expression += Utils::GetRationalString(Constants::Pi,1e17);
                        i += s.length()-1;
                    }else if (s == "e") {
                        t_expression += Utils::GetRationalString(Constants::e,1e17);
                        i += s.length()-1;
                    }
                }else {
                    t_expression += expression[i];
                }
            }
            expression = t_expression;
        }

        //Resolve Log Functions
        std::string t_expression = "";
        for(int i = 0 ; i < expression.length() ; i++) {
            if(expression.substr(i,3) == "log") {
                i += 3;
                std::string base_str = "";
                while (expression[i] != '(') {
                    base_str += expression[i];
                    i++;
                }
                i++;

                if (base_str == "") {
                    base_str = "10";
                }

                int counter = 1;
                std::string sub_exp = "";
                while (counter != 0) {
                    char _c = expression[i];
                    if (_c == '(') {
                        counter++;
                        sub_exp += _c;
                    }
                    else if (_c == ')') {
                        counter--;
                        if (counter != 0) {
                            sub_exp += _c;
                        }
                    }else {
                        sub_exp += _c;
                    }
                    i++;
                }
                ExpressionEvaluater sub_evaluator;
                Rational sub_value = log(sub_evaluator.evaluateExpression(sub_exp))/log(std::stold(base_str));
                t_expression += Utils::GetRationalString(sub_value,1e17);
                i--;
            }else {
                t_expression += expression[i];
            }
        }

        expression = t_expression;



        //Resolve Functions
        for (std::string s : functions) {
            std::string t_expression = "";
            for (int i = 0 ; i < expression.length() ; i++) {
                if (expression.substr(i,s.length()) == s) {
                    std::string sub_exp = "";
                    int counter = 1;
                    i += s.length() + 1;
                    while (counter != 0) {
                        char _c = expression[i];
                        if (_c == '(') {
                            counter++;
                            sub_exp += _c;
                        }
                        else if (_c == ')') {
                            counter--;
                            if (counter != 0) {
                                sub_exp += _c;
                            }
                        }else {
                            sub_exp += _c;
                        }
                        i++;
                    }
                    ExpressionEvaluater sub_evaluator;
                    Rational sub_value;
                    if (s == "sin") {
                        sub_value = Functions::Sin(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "cos") {
                        sub_value = Functions::Cos(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "tan") {
                        sub_value = Functions::Tan(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "cot") {
                        sub_value = Functions::Cot(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "cosec") {
                        sub_value = Functions::Cosec(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "sec") {
                        sub_value = Functions::Sec(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "arcsin") {
                        sub_value = Functions::Arcsin(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "arccos") {
                        sub_value = Functions::Arccos(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "arctan") {
                        sub_value = Functions::Arctan(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "ln") {
                        sub_value = Functions::Loge(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "sqrt") {
                        sub_value = Functions::Sqrt(sub_evaluator.evaluateExpression(sub_exp));
                    }else if (s == "mod") {
                        sub_value = Functions::Modulus(sub_evaluator.evaluateExpression(sub_exp));
                    }

                    t_expression += Utils::GetRationalString(sub_value,1e17);
                    i--;

                }else {
                    t_expression += expression[i];
                }
            }
            expression = t_expression;
        }

        evaluateArithmetic(expression);
        return value;


    }
}

}

