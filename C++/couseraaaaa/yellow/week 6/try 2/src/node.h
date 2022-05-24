#pragma once
#include <string>
#include <memory>
#include "date.h"
#include "Helpclasses.h"




class Node{
public:
	virtual bool Evaluate(const Date& date, const string& event) const=0;
};

class  EmptyNode{
public:
	bool Evaluate(const Date& date, const string& event) const override{
		return false;
	}
};

class DateComparisonNode{
public:

	//de>(cmp, ParseDate(is));
	DateComparisonNode(const Comparison& cmp, const Date& d){
		date_=d;
		oper_=cmp;
	}
	bool Evaluate(const Date& date, const string& event) const override{
		if(oper_ == Comparison::Less){return date < date_; }
		if(oper_ == Comparison::LessOrEqual){return date <= date_; }
		if(oper_ == Comparison::Greater){return date > date_; }
		if(oper_ == Comparison::GreaterOrEqual){return date >= date_; }
		if(oper_ == Comparison::Equal){return date = date_; }
		if(oper_ == Comparison::NotEqual){return date != date_; }
		return false;
	}
private:
	Comparison oper_;
    Date date_;
};

class EventComparisonNode{
public:
	EventComparisonNode(const Comparison& cmp, const string& event){
		oper_=cmp;
		event_=event;
	}
	bool Evaluate(const Date& date, const string& event) const override{
		if(oper_ == Comparison::Less){return event < event_; }
		if(oper_ == Comparison::LessOrEqual){return event <= event_; }
		if(oper_ == Comparison::Greater){return event > event_; }
		if(oper_ == Comparison::GreaterOrEqual){return event >= event_; }
		if(oper_ == Comparison::Equal){return event = event_; }
		if(oper_ == Comparison::NotEqual){return event != event_; }
		return false;
			}
private:
	Comparison oper_;
    string event_;

};

class LogicalOperationNode{
public:
	LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node> left,
			const shared_ptr<Node> right){
		oper_=op;
		left_=left;
		right_=right;
	}
	bool Evaluate(const Date& date, const string& event) const override{
		if(oper_==LogicalOperation::And){
			return left_.Evaluate(date,event)&&right_.Evaluate(date,event);
		}
		else if(oper_ == LogicalOperation::Or){
			return left_.Evaluate(date,event)||right_.Evaluate(date,event);
		}
		return false;
	}

private:
	LogicalOperation oper_;
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;
};
