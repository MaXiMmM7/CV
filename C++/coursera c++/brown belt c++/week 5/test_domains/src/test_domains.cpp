#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

template <typename It>
class Range {
public:
  Range(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

private:
  It begin_;
  It end_;
};

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

vector<string_view> Split(string_view s, string_view delimiter = " ") {
  vector<string_view> parts;
  if (s.empty()) {
    return parts;
  }
  while (true) {
    const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    parts.push_back(lhs);
    if (!rhs_opt) {
      break;
    }
    s = *rhs_opt;
  }
  return parts;
}


class Domain {
public:
  explicit Domain(string_view text) {
    vector<string_view> parts = Split(text, ".");
    parts_reversed_.assign(rbegin(parts), rend(parts));
  }

  size_t GetPartCount() const {
    return parts_reversed_.size();
  }

  auto GetParts() const {
    return Range(rbegin(parts_reversed_), rend(parts_reversed_));
  }
  auto GetReversedParts() const {
    return Range(begin(parts_reversed_), end(parts_reversed_));
  }

  bool operator==(const Domain& other) const {
    return parts_reversed_ == other.parts_reversed_;
  }

private:
  vector<string> parts_reversed_;
};

ostream& operator<<(ostream& stream, const Domain& domain) {
  bool first = true;
  for (const string_view part : domain.GetParts()) {
    if (!first) {
      stream << '.';
    } else {
      first = false;
    }
    stream << part;
  }
  return stream;
}

// domain is subdomain of itself
bool IsSubdomain(const Domain& subdomain, const Domain& domain) {
  const auto subdomain_reversed_parts = subdomain.GetReversedParts();
  const auto domain_reversed_parts = domain.GetReversedParts();
  return
      subdomain.GetPartCount() >= domain.GetPartCount()
      && equal(begin(domain_reversed_parts), end(domain_reversed_parts),
               begin(subdomain_reversed_parts));
}

bool IsSubOrSuperDomain(const Domain& lhs, const Domain& rhs) {
  return lhs.GetPartCount() >= rhs.GetPartCount()
         ? IsSubdomain(lhs, rhs)
         : IsSubdomain(rhs, lhs);
}


class DomainChecker {
public:
  template <typename InputIt>
  DomainChecker(InputIt domains_begin, InputIt domains_end) {
    sorted_domains_.reserve(distance(domains_begin, domains_end));
    for (const Domain& domain : Range(domains_begin, domains_end)) {
      sorted_domains_.push_back(&domain);
    }
    sort(begin(sorted_domains_), end(sorted_domains_), IsDomainLess);
    sorted_domains_ = AbsorbSubdomains(move(sorted_domains_));
  }

  // Check if candidate is subdomain of some domain
  bool IsSubdomain(const Domain& candidate) const {
    const auto it = upper_bound(
        begin(sorted_domains_), end(sorted_domains_),
        &candidate, IsDomainLess);
    if (it == begin(sorted_domains_)) {
      return false;
    }
    return ::IsSubdomain(candidate, **prev(it));
  }

private:
  vector<const Domain*> sorted_domains_;

  static bool IsDomainLess(const Domain* lhs, const Domain* rhs) {
    const auto lhs_reversed_parts = lhs->GetReversedParts();
    const auto rhs_reversed_parts = rhs->GetReversedParts();
    return lexicographical_compare(
      begin(lhs_reversed_parts), end(lhs_reversed_parts),
      begin(rhs_reversed_parts), end(rhs_reversed_parts)
    );
  }

  static vector<const Domain*> AbsorbSubdomains(vector<const Domain*> domains) {
    domains.erase(
        unique(begin(domains), end(domains),
               [](const Domain* lhs, const Domain* rhs) {
                 return IsSubOrSuperDomain(*lhs, *rhs);
               }),
        end(domains)
    );
    return domains;
  }
};


vector<Domain> ReadDomains(istream& in_stream = cin) {
  vector<Domain> domains;

  size_t count;
  in_stream >> count;
  domains.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    string domain_text;
    in_stream >> domain_text;
    domains.emplace_back(domain_text);
  }
  return domains;
}

vector<bool> CheckDomains(const vector<Domain>& banned_domains, const vector<Domain>& domains_to_check) {
  const DomainChecker checker(begin(banned_domains), end(banned_domains));

  vector<bool> check_results;
  check_results.reserve(domains_to_check.size());
  for (const Domain& domain_to_check : domains_to_check) {
    check_results.push_back(!checker.IsSubdomain(domain_to_check));
  }

  return check_results;
}

void PrintCheckResults(const vector<bool>& check_results, ostream& out_stream = cout) {
  for (const bool check_result : check_results) {
    out_stream << (check_result ? "Good" : "Bad") << "\n";
  }
}

void TestSimple() {
	{//1) ѕри разбиении строки по разделителю в начало списка частей добавл€етс€ пуста€ строка.
		Domain dmn("hey.man.ru");
		ASSERT_EQUAL(dmn.GetReversedParts().begin()->empty(),false);
		ASSERT_EQUAL(dmn.GetParts().begin()->empty(),false);
	//2)ћетод GetReversedParts возвращает части домена в пр€мом пор€дке, а не в обратном.
		ASSERT_EQUAL(vector<string>(dmn.GetReversedParts().begin(),dmn.GetReversedParts().end()),vector<string>({"ru","man","hey"}));
	}
	{//3)ƒомен не считаетс€ своим поддоменом. ????????????????????
		vector<Domain> dms({Domain("man.ru"),Domain("com")});
		DomainChecker cheker(dms.begin(),dms.end());
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("com")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("man.ru")),true);

	//4)ѕри проверке того, €вл€етс€ ли один домен поддоменом другого, параметры перепутаны местами.
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru.man")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru.man.horse")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("com.hey")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("com.ru.man")),false);
	}
	{//5)ѕри инициализации DomainChecker не происходит поглощени€ поддоменов.
		vector<Domain> dms({Domain("a.ru"),Domain("a.b.ru"),Domain("b.a.ru"),Domain("ru"),Domain("c.a.b.ru")});
		DomainChecker cheker(dms.begin(),dms.end());
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("a.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("a.b.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("b.a.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("c.a.b.ru")),true);

		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.a.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.a.b.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.b.a.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.c.a.b.ru")),true);

		ASSERT_EQUAL(cheker.IsSubdomain(Domain("a.ru.hey")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("a.b.ru.hey")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("b.a.ru.hey")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru.hey")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("c.a.b.ru.hey")),false);

		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru.hey.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru.ru.ru")),true);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("ru.c.a")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.ru.hey")),false);
		ASSERT_EQUAL(cheker.IsSubdomain(Domain("hey.c.a.b.ru.hey")),false);

		vector<Domain> dms_empty_;
		DomainChecker cheker_empty_(dms_empty_.begin(),dms_empty_.end());
		ASSERT_EQUAL(cheker_empty_.IsSubdomain(Domain("a.ru")),false);
		ASSERT_EQUAL(cheker_empty_.IsSubdomain(Domain("a.b.ru")),false);
		ASSERT_EQUAL(cheker_empty_.IsSubdomain(Domain("b.a.ru")),false);
		ASSERT_EQUAL(cheker_empty_.IsSubdomain(Domain("ru")),false);
		ASSERT_EQUAL(cheker_empty_.IsSubdomain(Domain("c.a.b.ru")),false);
	}
	{//6)ѕри проверке доменов по данному набору успехом считаетс€ ситуаци€,
		//когда домен-запрос €вл€етс€ поддоменом одного из запрещЄнных.

	}
	{//7)ѕри выводе перепутаны Good и Bad.
		vector<Domain> bad({Domain("ru"),Domain("com"),Domain("hey.com"),Domain("hey.man.yes"),
			Domain("bad.fly.fly"),Domain("fly"),Domain("cat")});
		vector<Domain> check({Domain("ru"),Domain("com"),Domain("hey.com"),Domain("hey.man.yes"),
			Domain("bad.fly.fly"),Domain("fly"),Domain("cat"),
			Domain("bro.ru"),Domain("bro.com"),Domain("bro.hey.com"),Domain("bro.hey.man.yes"),
			Domain("bro.bad.fly.fly"),Domain("bro.fly"),Domain("bro.cat"),
			Domain("ru.bro"),Domain("com.bro"),Domain("hey.com.bro"),Domain("hey.man.yes.bro"),
			Domain("bad.fly.fly.bro"),Domain("fly.bro"),Domain("cat.bro")});
		vector<bool> v({false,false,false,false,false,false,false,false,false,false,false,false,false,false,
			true,true,true,true,true,true,true});
		string out_string_("Bad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\nBad\n"
				"Good\nGood\nGood\nGood\nGood\nGood\nGood\n");
		ASSERT_EQUAL(CheckDomains(bad,check),v);

		ostringstream output1;
		PrintCheckResults(CheckDomains(bad,check),output1);
		ASSERT_EQUAL(output1.str(),out_string_);

		vector<Domain> empty_;
		vector<bool> v_emty_({true,true,true,true,true,true,true,true,true,true,true,true,true,true,
					true,true,true,true,true,true,true});
		ASSERT_EQUAL(CheckDomains(empty_,check),v_emty_);

		ostringstream output2;
		string out_string_2("Good\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\nGood\n"
				"Good\nGood\nGood\nGood\nGood\nGood\n");
		PrintCheckResults(CheckDomains(empty_,check),output2);
		ASSERT_EQUAL(output2.str(),out_string_2);
	}
	{//8)ѕри считывании доменов из-за неаккуратного использовани€ getline первый домен всегда считываетс€ пустым.
		istringstream s("5\nru\nhey.ru\ncom\nbro\ncheck.lol\n");
		vector<Domain> domains=ReadDomains(s);
		ASSERT_EQUAL(static_cast<int>(domains.size()),5);
		ASSERT_EQUAL((domains[0]==Domain("")),false);

		istringstream s1("0");
		domains=ReadDomains(s1);
		ASSERT_EQUAL(static_cast<int>(domains.size()),0);
	}
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);

  const vector<Domain> banned_domains = ReadDomains();
  const vector<Domain> domains_to_check = ReadDomains();
  PrintCheckResults(CheckDomains(banned_domains, domains_to_check));
  return 0;
}
