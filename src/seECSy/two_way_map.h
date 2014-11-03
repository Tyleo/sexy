#pragma once

namespace tyleo
{
    template <typename TKey, typename TItem>
    using tyleo_unordered_map = std::unordered_map<TKey, TItem>;

    template <typename TItem>
    using tyleo_set = std::unordered_set<TItem>;

    template <typename TItem0,
        typename TItem1,
        template<typename, typename> class TMap = tyleo_unordered_map,
        template<typename> class TSet = tyleo_set>
    class TwoWayMap final
    {
    private:
        TMap<TItem0, TSet<TItem1>> _item0ToItem1Map;
        TMap<TItem1, TSet<TItem0>> _item1ToItem0Map;

    public:
        void AddItem0ToItem1(TItem0 item0, TItem1 item1)
        {
            _item0ToItem1Map.at(item1).insert(item0);
            _item1ToItem0Map.at(item0).insert(item1);
        }

        void AddItem1ToItem0(TItem1 item1, TItem0 item0)
        {
            _item1ToItem0Map.at(item0).insert(item1);
            _item0ToItem1Map.at(item1).insert(item0);
        }

        void AddItem0(TItem0 item0)
        {
            _item0ToItem1Map.emplace(std::make_pair(item0, TSet < TItem1 > {}));
        }

        void AddItem1(TItem1 item1)
        {
            _item1ToItem0Map.emplace(std::make_pair(item1, TSet < TItem0 > {}));
        }

        void RemoveItem0FromItem1(TItem0 item0, TItem1 item1)
        {
            _item0ToItem1Map.at(item0).erase(item1);
            _item1ToItem0Map.at(item1).erase(item0);
        }

        void RemoveItem1FromItem0(TItem1 item1, TItem0 item0)
        {
            _item1ToItem0Map.at(item1).erase(item0);
            _item0ToItem1Map.at(item0).erase(item1);
        }

        void RemoveItem0(TItem0 item0)
        {
            for (auto item1 : _item0ToItem1Map.at(item0))
            {
                _item1ToItem0Map.at(item1).erase(item0);
            }

            _item0ToItem1Map.erase(item0);
        }

        void RemoveItem1(TItem1 item1)
        {
            for (auto item0 : _item1ToItem0Map.at(item1))
            {
                _item0ToItem1Map.at(item0).erase(item1);
            }

            _item1ToItem0Map.erase(item1);
        }

        TwoWayMap() : _item0ToItem1Map{},
            _item1ToItem0Map{}
        {}
    };
}
