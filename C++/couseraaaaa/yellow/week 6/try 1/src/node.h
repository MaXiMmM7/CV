#pragma once

#include "ComparisonAndLogical.h"
#include "date.h"



#include <string>
#include <memory>
using namespace std;

class Node{
public:
	virtual bool Evaluate(const Date& date, const string& event) const =0;
};

class EmptyNode: public Node{
	public:
	bool Evaluate(const Date& date, const string& event) const override{return false;}
};

class DateComparisonNode:public Node{
public:
	DateComparisonNode(const Comparison& cmp,const Date& date);
	//<DateComparisonNode>(cmp, ParseDate(is));

	bool Evaluate(const Date& date, const string& event) const override{
		 if(cmp == Comparison::Equal){return date==helper;}
		 else if (cmp == Comparison::Greater){return date>helper;}
		 else if(cmp == Comparison::GreaterOrEqual){return date>=helper;}
		 else if(cmp == Comparison::Less){return date<helper;}
		 else if(cmp == Comparison::LessOrEqual){return date<=helper;}
		 else if(cmp == Comparison::NotEqual){return date!=helper;}
		 return false;
		}


private:
	Comparison cmp;
	Date helper;
};

class EventComparisonNode:public Node{
public:
	EventComparisonNode(const Comparison& cmp,const string& event);
	//<DateComparisonNode>(cmp, ParseDate(is));

	bool Evaluate(const Date& date, const string& event) const override{
		 if(cmp == Comparison::Equal){return event==helper;}
		 else if (cmp == Comparison::Greater){return event>helper;}
		 else if(cmp == Comparison::GreaterOrEqual){return event>=helper;}
		 else if(cmp == Comparison::Less){return event<helper;}
		 else if(cmp == Comparison::LessOrEqual){return event<=helper;}
		 else if(cmp == Comparison::NotEqual){return event!=helper;}
		 return false;
		}


private:
	Comparison cmp;
	string helper;
};

class LogicalOperationNode: public Node{
public:
	LogicalOperationNode(const LogicalOperation& logical_operation,shared_ptr<Node> node_left,
			shared_ptr<Node> node_right);

	bool Evaluate(const Date& date, const string& event) const override{
			 if(operation == LogicalOperation::And){
				 return left_->Evaluate(date,event)&&right_->Evaluate(date,event);
			 }
			 else if (operation == LogicalOperation::Or){
				 return left_->Evaluate(date,event)||right_->Evaluate(date,event);
			 }
			  return false;
			}
private:
	LogicalOperation operation;
	shared_ptr<const Node> left_,right_;
};
