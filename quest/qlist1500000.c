mapping *quest = ({
     ([      "quest":                "��ħ��",
        "diff":                 10,
        ]),
     ([      "quest":                 "�����" ,
        "diff":                 9,
        ]),
     ([      "quest":                BLK "��⬼�" NOR,
        "diff":                 8,
        ]),
     ([      "quest":                "����",
        "diff":                 7,
        ]),
     ([      "quest":                HIW "��" NOR,
        "diff":                 6,
        ]),
     ([      "quest":                HIW "��" NOR,
        "diff":                 5,
        ]),
     ([      "quest":                HIW "����" NOR,
        "diff":                 4,
        ]),
     ([      "quest":                HIY  "����" NOR,
        "diff":                 4,
        ]),
     ([      "quest":                "�������澭���²�",
        "diff":                 10,
        ]),
     ([      "quest":                "������",
        "diff":                 6,
        ]),
     ([      "quest":                MAG "��֬��" NOR,
        "diff":                 6,
        ]),
     ([      "quest":                "�������澭���ϲ�",
        "diff":                 6,
        ]),
     ([      "quest":                "�л���",
        "diff":                 6,
        ]),

});
mapping query_quest()
{
        return quest[random(sizeof(quest))];
}