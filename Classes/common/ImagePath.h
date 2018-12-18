//
//  ImagePath.h
//


#ifndef __TwoMahjong__ImagePath__
#define __TwoMahjong__ImagePath__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
static string IMG_PRE = "images/";//images/
static char AVATAR_ANIMATION_PATH[] = "images/avatar/animation/%s.ExportJson";

static char AVATAR_HEAD_PATH[] = "images/avatar/head/%s.png";

static char AVATAR_HEROBODY_PATH[] = "images/avatar/halfbody/%s.png";
static char IMAGE_FAMOUSE_BOSS[] = "images/avatar/famouseBoss/image_famouse_boss.png";//名将传boss
static char BEGAIN_VIDEO[] = "move_begain";
static char IMG_BATTLE_CONTROLBAR[] = "images/battle/image_battle_controlBar.png";
static char IMG_SCENE_EFFECT[] = "images/battle/effect/%s.ExportJson";

static char IMG_BATTLE_SMALLMAP[] = "images/cardPic/%s.png";//战斗小地图资源
static char IMG_BATTLEINFO_SMALLMAP[] = "images/stageBattleInfo/smallMap/%s.png";
static char IMG_PUBLIC_ITEM[]="images/icon/item/%s.png";

//--------------------------------------公共资源//--------------------------------------//

//static char IMG_PUBLIC_LOGO[] = "images/public/image_public_logo.png";//logo

static char IMG_PUBLIC_BACKBTN[] = "images/public/image_public_backBtn.png";
static char IMG_PUBLIC_SHADOW[] = "images/public/image_public_shadow.png";//阴影
static char IMG_PUBLIC_MASK[] = "images/public/image_public_mask.png";//遮罩
static char IMG_PUBLIC_FLOATLABELBG[] = "images/public/image_public_FloatLabelBg.png";
static char IMG_PUBLIC_STAR[] = "images/public/image_public_star.png";//公共星星
static char IMG_PUBLIC_LEVELUP[] = "images/public/image_public_levelUp.png";//升级
static char IMG_PUBLIC_FUNCTIONOPEN[] = "images/public/image_public_functionOpen.png";//新功能开启
static char IMG_PUBLIC_TIPSBG[] = "images/public/image_public_tipsBg.png";//tipsbg
static char IMG_PUBLIC_BOXCLOSE[] = "images/public/image_public_boxClose.png";//宝箱关闭
static char IMG_PUBLIC_BOXOPEN[] = "images/public/image_public_boxOpen.png";//宝箱关闭
static char IMG_PUBLIC_HEROHEADBOX[] = "images/public/image_public_heroBox.png";//头像背景框
static char IMG_PUBLIC_HEROHEADBG[] = "images/public/heroInfo/image_public_heroBg2.png";//头像背景框
static char IMG_PUBLIC_AVATARNAMMEBG[] = "images/public/image_public_avatarNameBg.png";//人物名字背景
static char IMG_PUBLIC_AVATAR_BLOODBG[] = "images/public/image_public_avatarBloodBg.png";//人物血条背景
static char IMG_PUBLIC_AVATAR_BLOOD[] = "images/public/image_public_avatarBlood.png";//人物血条
static char IMG_PUBLIC_AVATAR_BLOOD_WHITE[] = "images/public/image_public_avatarWhiteBlood.png";//人物血条

static char IMG_PUBLIC_LAYER_LEAD[] = "images/public/layer/images_public_layer_lead.png";//领导力
static char IMG_PUBLIC_MILITARY[] = "images/public/layer/images_public_layer_milit.png";//列表战力
//static char IMG_PUBLIC_HEROHEAD_PRESTIGE[] = "images/public/layer/images_public_head_prest.png";//头像声望
static char IMG_PUBLIC_HEROHEAD_LEVEL[] = "images/public/layer/images_public_head_rank_bg.png";//头像等级
static char IMG_PUBLIC_HEADTALENTFRAME[]="images/public/heroInfo/image_public_headTalentFrame%d.png";//头像品质框
static char IMG_PUBLIC_HEROHEADFRAMEBG[] = "images/public/heroInfo/image_public_heroBg%d.png";//
static char IMG_PUBLIC_LAYER_STAR[] = "images/public/layer/image_public_layer_star.png";//紫色星星
static char IMG_PUBLIC_LAYER_LISTBG[] = "images/public/layer/image_public_layer_listBg.png";//武将list背景
static char IMG_PUBLIC_LAYER_LISTBGTITLEBG[] = "images/public/layer/image_public_listBgTitle.png";//背景标题底层
static char IMG_PUBLIC_LAYER_FRAGMENT[] = "images/public/layer/image_public_layer_fragment.png";//碎片
static char IMG_PUBLIC_LAYER_BOOK[] = "images/public/layer/image_public_layer_book.png";//碎片
static char IMG_PUBLIC_HEAD_STARBG[] = "images/public/layer/image_public_head_starBg.png";//武将头像星星背景


static char IMG_PUBLIC_LAYER_CDKEY_INPUTBG[] = "images/public/layer/image_public_layer_cdkey_inputBg.png";//兑换输入背景
//image_public_layer_fragment
static char IMG_PUBLIC_LAYER_LISTBG2[] = "images/public/layer/image_public_layer_listBg2.png";//武将list背景2
static char IMG_PUBLIC_LAYER_TWO_CELLBG[] = "images/public/layer/images_table_two_cellbg.png";//武将listCell背景
static char IMG_PUBLIC_LAYER_SELLBG[] = "images/public/layer/image_public_layer_sellBg.png";//出售背景
static char IMG_PUBLIC_LAYER_RANKCELLBG[] = "images/public/layer/image_public_layer_rankcellbg.png";//排名背景

static char IMG_PUBLIC_LAYER_LEFTLISTBG[] = "images/public/layer/images_public_layer_leftListBg.png";//武将or装备小列表背景；
static char IMG_PUBLIC_EQUIP_NAMEBG[] = "images/public/layer/images_table_equip_nameBg.png";//装备名字背景；
static char IMG_PUBLIC_LAYER_DRESS[] = "images/public/layer/image_public_layer_dress.png";//穿戴
static char IMG_PUBLIC_LAYER_FIGHT[] = "images/public/layer/image_public_layer_fight.png";//出战
static char IMG_PUBLIC_HEROHEADFRAMEBGS[] = "images/public/heroInfo/image_public_heroBg%s.png";//头像品质背景框
static char IMG_PUBLIC_HEADTALENTFRAMES[]="images/public/heroInfo/image_public_headTalentFrame%s.png";//头像品质框
static char IMG_MARKET_AUCTION_CELLBGBOX[]="images/public/layer/image_public_layer_boxbg.png";//头像品质框
static char IMG_PUBLIC_LAYER__CELLTITLEBG[]="images/public/layer/image_public_layer_celltitlebg.png";//celltitle背景

//static char IMG_PUBLIC_DOT[] = "images/public/image_public_dot.png";//红点
static char IMG_PUBLIC_HEADBIGFRAME[]="images/public/heroInfo/image_public_headBigFrame%d.png";//大卡牌品质框
static char IMG_PUBLIC_HEADNAMEBG[]="images/public/heroInfo/image_public_headNameBg%d.png";//名字背景框
static char IMG_PUBLIC_HEROINFO_FORCE[]="images/public/heroInfo/image_public_hero_force%d.png";//武将势力
static char IMG_PUBLIC_HEROINFO_FORCECIRCLE[]="images/public/heroInfo/image_public_hero_forceCircle%d.png";//武将势力圆形
static char IMG_PUBLIC_HEROINFO_ATTACTTYPE[]="images/public/heroInfo/image_public_Attacttype%d.png";//攻击类型
static char IMG_PUBLIC_TASK_TARGET[] = "images/public/image_public_taskTarget.png";
static char IMG_PUBLIC_DOWNARROW[] = "images/public/image_public_downArrow.png";//目标箭头
static char IMG_SWEEP_BG[] = "images/public/dialog/image_public_sweepBg.jpg";
static char IMG_PUBLIC_STAGEBG[] = "images/public/dialog/image_public_stagebg.jpg";
static char IMG_PUBLIC_MENUSHOWBTN[] = "images/public/menuBar/menuShowBtn.png";

static char IMG_PUBLIC_MENUBTN_LINEUP[] = "images/public/menuBar/menuBtn_lineup.png";
static char IMG_PUBLIC_MENUBTN_MARKET[] = "images/public/menuBar/menuBtn_market.png";
static char IMG_PUBLIC_MENUBTN_TASK[] = "images/public/menuBar/menuBtn_task.png";//任务
static char IMG_PUBLIC_MENUBTN_ACATIVE[] = "images/public/menuBar/menuBtn_acative.png";//活动

static char IMG_PUBLIC_MENUBTN_WAR[] = "images/public/menuBar/menuBtn_war.png";
static char IMG_PUBLIC_MENUBTN_IMPER[] = "images/public/menuBar/menuBtn_imper.png";
static char IMG_PUBLIC_MENUBTN_SEVEN[] = "images/public/menuBar/menuBtn_seven.png";
static char IMG_PUBLIC_MENUBTN_FIGHTER[] = "images/public/menuBar/menuBtn_fighter.png";//名将转
//
static char IMG_PUBLIC_MENUBTN_ACTIVEBOX[]="images/public/menuBar/menuBtn_activeBox.png";
static char IMG_PUBLIC_MENUBTN_RECHARGE[] = "images/public/menuBar/menuBtn_recharge.png";//充值
static char IMG_PUBLIC_MENUBTN_MAIL[] = "images/public/menuBar/menuBtn_mail.png";//邮件
static char IMG_PUBLIC_MENUBTN_QIANDAO[] = "images/public/menuBar/menuBtn_qiandao.png";//签到
static char IMG_PUBLIC_MENUBTN_CDKEY[] = "images/public/menuBar/menuBtn_cdkey.png";//兑换
static char IMG_PUBLIC_MENUBTN_LIMIT[] = "images/public/menuBar/menuBtn_limit.png";//招募

static char IMG_PUBLIC_MENUBTN_GIFT[] = "images/public/menuBar/menuBtn_gift.png";//礼包
static char IMG_PUBLIC_MENUBTN_SHOP[] = "images/public/menuBar/menuBtn_shop.png";//商场
static char IMG_PUBLIC_MENUBTN_EQUIP[] = "images/public/menuBar/menuBtn_equip.png";//装备
static char IMG_PUBLIC_MENUBTN_GENERAL[] = "images/public/menuBar/menuBtn_general.png";//武将
static char IMG_PUBLIC_MENUBTN_FIGHTING[] = "images/public/menuBar/menuBtn_fighting.png";//竞技场

static char IMG_PUBLIC_MENUBTN_BOX[] = "images/public/menuBar/menuBtn_box.png";//背包
static char IMG_PUBLIC_MENUBTN_BOOK[] = "images/public/menuBar/menuBtn_book.png";//书卷
static char IMG_PUBLIC_MENUBTN_BOOK2[] = "images/public/menuBar/menuBtn_book2.png";//书卷2
static char IMG_PUBLIC_MENUBTN_JUXIAN[] = "images/public/menuBar/menuBtn_juxian.png";//聚贤
static char IMG_PUBLIC_MENUBTN_WEAL[] = "images/public/menuBar/menuBtn_weal.png";//福利
static char IMG_PUBLIC_MENUBTN_PRAY[] = "images/public/menuBar/menuBtn_pray.png";//祈福
static char IMG_PUBLIC_MENUBTN_DOWN[] = "images/public/menuBar/menuBtn_down.png";//下按钮
static char IMG_PUBLIC_MENUBTN_UP[] = "images/public/menuBar/menuBtn_up.png";//上按钮
static char IMG_PUBLIC_LAYER_GAIN_BG[] = "images/public/layer/image_public_layer_gain_bg.png";//获得奖励背景
static char IMG_PUBLIC_LAYER_GAIN_LABEL[] = "images/public/layer/image_public_layer_gain_label.png";//获得奖励label
//

static char IMG_PUBLIC_MODULE_BG[] ="images/public/dialog/image_public_module_bg.png";//
static char IMG_PUBLIC_MODULE_BG2[] ="images/public/dialog/image_public_module_bg2.png";//
static char IMG_PUBLIC_LATTER_BG[] ="images/public/dialog/img_public_latter_bg.png";//书信
static char IMG_PUBLIC_EQUIP_BG[] ="images/public/dialog/img_public_equip_bg.jpg";//装备
static char IMG_PUBLIC_MATERIAL_BG[] ="images/public/dialog/img_public_material_bg.jpg";//道具

static char IMG_PUBLIC_TITLE_BG[] ="images/public/dialog/image_public_title_bg.png";

static char IMG_PUBLIC_MODULE_MASK_TOP[] ="images/public/dialog/image_public_module_mask_top.png";
static char IMG_PUBLIC_MODULE_MASK_BOTTOM[] ="images/public/dialog/image_public_module_mask_bottom.png";
static char IMG_PUBLIC_TABLE_VIEW_SHADE[] ="images/public/dialog/image_public_table_view_shade.png";

static char IMG_PUBLIC_NUMBER1[] = "images/public/number/number1.png";
static char IMG_PUBLIC_NUMBER2[] = "images/public/number/number2.png";
static char IMG_PUBLIC_NUMBER3[] = "images/public/number/number3.png";
static char IMG_PUBLIC_NUMBER4[] = "images/public/number/number4.png";
static char IMG_PUBLIC_NUMBER5[] = "images/public/number/number5.png";
static char IMG_PUBLIC_NUMBER6[] = "images/public/number/number6.png";
static char IMG_PUBLIC_NUMBER7[] = "images/public/number/number7.png";
static char IMG_PUBLIC_MINUTES[] = "images/public/number/img_number_minus.png";
static char IMG_DIALOG_BG[] = "images/public/dialog/image_public_dialogBg.png";
static char IMG_DIALOG_BG1[] = "images/public/dialog/image_public_dialogBg1.png";

static char IMG_BUTTON_TWO_BLUEBTN1[] = "images/public/button/image_public_button_two_blueBtn1.png";
static char IMG_BUTTON_TWO_BLUEBTN2[] = "images/public/button/image_public_button_two_blueBtn2.png";
static char IMG_BUTTON_FOUR_GREENBTN1[] = "images/public/button/image_public_four_greenbtn1.png";
static char IMG_BUTTON_FOUR_GREENBTN2[] = "images/public/button/image_public_four_greenbtn2.png";

static char IMG_PUBLIC_BUTTON_FOUR_YELLOW[] = "images/public/button/image_public_button_four_yellow.png";
static char IMG_PUBLIC_BUTTON_FOUR_GREEN[] = "images/public/button/image_public_button_four_red.png";
static char IMG_PUBLIC_BUTTON_CUSP_FOUR_BLUE[] = "images/public/button/image_public_button_cusp_four_blue.png";
static char IMG_PUBLIC_BUTTON_CUSP_FOUR_GREEN[] = "images/public/button/image_public_button_cusp_four_green.png.png";


static char IMG_PUBLIC_BUTTON_TWO_RED[] = "images/public/button/image_public_button_two_red.png";
static char IMG_PUBLIC_BUTTON_FOUR_RED[] = "images/public/button/image_public_button_four_red.png";
static char IMG_PUBLIC_BUTTON_TWO_ORANGE[] = "images/public/button/image_public_button_two_orange.png";
static char IMG_PUBLIC_BUTTON_TWO_SMALLORANGE[] = "images/public/button/image_public_button_smallTwo_orange.png";
static char IMG_PUBLIC_BUTTON_TWO_SMALLORED[] = "images/public/button/image_public_button_smallTwo_red.png";

static char IMG_PUBLIC_BUTTON_FOUR_ORANGE[] = "images/public/button/image_public_button_four_orange.png";

static char IMG_PUBLIC_BUTTON_SIGNIN_YELLOW[] = "images/public/button/image_public_button_signin_yellow.png";
static char IMG_PUBLIC_BUTTON_SIGNIN_GREEN[] = "images/public/button/image_public_button_signin_green.png";

static char IMG_PUBLIC_BUTTON_GREEN[] = "images/public/button/image_public_button_green.png";
static char IMG_PUBLIC_BUTTON_GOTO[] = "images/public/button/image_public_goto.png";//前往
static char IMG_PUBLIC_BUTTON_GETPRIZE[] = "images/public/button/image_public_button_getPrize.png";//领取奖励
static char IMG_BUTTON_ENTERBTN[] = "images/public/button/image_public_enterbtn.png";//进入游戏按钮背景
static char IMG_BUTTON_CONFIRM_LABEL[] = "images/public/button/image_pubilc_button_ConfirmLabel.png";//确定
static char IMG_BUTTON_CANCEL_LABEL[] = "images/public/button/image_pubilc_button_CancelLabel.png";//取消
static char IMG_BUTTON_REDBTN[] = "images/public/button/image_public_redBtn.png";//红色按钮
static char IMG_BUTTON_BYTTON_XITONGGAOGAO[] = "images/public/button/image_pubilc_button_xiotngbtn.png";//系统公告
static char IMG_BUTTON_BYTTON_XITONGGAOGAOWORD[] = "images/public/button/image_pubilc_button_xiotngWord.png";//系统公告字
static char IMG_BUTTON_BYTTON_TUICHUBTN[] = "images/public/button/image_pubilc_button_tuichubtn.png";//退出游戏
static char IMG_BUTTON_BYTTON_TUICHUBTNWORD[] = "images/public/button/image_pubilc_button_tuichuWord.png";//退出游戏字
static char IMG_BUTTON_BYTTON_NANEBTNWORD[] = "images/public/button/image_public_button_naneBtnWord.png";//确定名字字
static char IMG_BUTTON_BYTTON_NANEBTN[] = "images/public/button/image_public_button_naneBtn.png";//确定名字
static char IMG_BUTTON__SAODANGONE[] = "images/public/button/image_pubilc_button_saodangOne.png";//扫荡一次
static char IMG_BUTTON__DAODANGFIVE[] = "images/public/button/image_pubilc_button_saodangFive.png";//扫荡5次
static char IMG_BUTTON_REQUESTTITLE[] = "images/public/button/img_public_button_requestTitle.png";//申请标题
static char IMG_BUTTON_REBORNLABEL[] = "images/public/button/image_public_reBornLabel.png";//复活
static char IMG_BUTTON_NOLABEL[] = "images/public/button/image_public_noLabel.png";//否
static char IMG_BUTTON_BIGYELLOW[] = "images/public/button/image_pubilc_button_bigyellow.png";//大黄色按钮
static char IMG_BUTTON_BIGLINGQU[] = "images/public/button/image_pubilc_button_biglingqu.png";//大领取



static char IMG_PUBLIC_COMBOBOX_BG[] = "images/public/comboBoxBtn/images_public_comboBox_bg.png";//comboxBtn背景
static char IMG_PUBLIC_COMBOBOX_BTN2[] = "images/public/comboBoxBtn/images_public_comboBox_btn2.png";//comboxBtn按钮
static char IMG_PUBLIC_COMBOBOX_BTN1[] = "images/public/comboBoxBtn/images_public_comboBox_btn1.png";//comboxBtn按钮
static char IMG_PUBLIC_COMBOBOX_BTNCIRCLE1[] = "images/public/comboBoxBtn/images_public_comboBox_btnciecle1.png";//comboxBtn圆按钮
static char IMG_PUBLIC_COMBOBOX_BTNCIRCLE2[] = "images/public/comboBoxBtn/images_public_comboBox_btnciecle2.png";//comboxBtn圆按钮


static char IMG_PUBLIC_COMBOBOX_PAR1[] = "images/public/comboBoxBtn/images_public_comboBox_par1.png";//优先按钮
static char IMG_PUBLIC_COMBOBOX_PAR2[] = "images/public/comboBoxBtn/images_public_comboBox_par2.png";//优先按钮

static char IMG_PUBLIC_COMBOBOX_FRIST1[] = "images/public/comboBoxBtn/images_public_comboBox_frist1.png";//新优先按钮
static char IMG_PUBLIC_COMBOBOX_FRIST2[] = "images/public/comboBoxBtn/images_public_comboBox_frist2.png";//新优先按钮
static char IMG_PUBLIC_COMBOBOX_CHOOSE2[] = "images/public/comboBoxBtn/images_public_comboBox_choose2.png";//新comboxBtn按钮
static char IMG_PUBLIC_COMBOBOX_CHOOSE1[] = "images/public/comboBoxBtn/images_public_comboBox_choose1.png";//新comboxBtn按钮

static char IMG_PUBLIC_COMBOBOX_BTNCHOSE[] = "images/public/comboBoxBtn/images_public_comboxbtnchose.png";//按钮选中
static char IMG_PUBLIC_COMBOBOX_BTNUNCHOSE[] = "images/public/comboBoxBtn/images_public_comboxbtnunchose.png";//按钮未选中

static char IMG_PUBLIC_COMBOBOX_RANK1[] = "images/public/comboBoxBtn/images_public_comboBox_rank1.png";//排序未选中
static char IMG_PUBLIC_COMBOBOX_RANK2[] = "images/public/comboBoxBtn/images_public_comboBox_rank2.png";//排序选中



static char IMG_PUBLIC_TABLEVIEW_CELLBG[] = "images/public/dialog/tableView/images_public_tableView_cellBg.png";//列表背景
static char IMG_PUBLIC_TABLEVIEW_GETBG[] = "images/public/dialog/tableView/images_public_tableView_getBg.png";//获取列表背景
static char IMG_PUBLIC_TABLEVIEW_HERO[] = "images/public/dialog/tableView/images_public_tableView_hero.png";//武将默认框
static char IMG_PUBLIC_TABLEVIEW_EQUIP[] = "images/public/dialog/tableView/images_public_tableView_equip.png";//装备默认框
static char IMG_PUBLIC_TABLEVIEW_EQUIP2[] = "images/public/dialog/tableView/images_public_tableView_equip2.png";//装备默认框

static char IMG_PUBLIC_TABLEVIEW_BG[] = "images/public/dialog/tableView/images_public_tableView_bg.png";//tableview背景
static char IMG_PUBLIC_TABLEVIEW_FOUR_BTN[] = "images/public/dialog/tableView/images_public_tableView_four_btn.png";//tableview按钮2
static char IMG_PUBLIC_TABLEVIEW_TWO_BTN[] = "images/public/dialog/tableView/images_public_tableView_two_btn.png";//tableview按钮1
static char IMG_PUBLIC_TABLEVIEW_NAME_BG[] = "images/public/dialog/tableView/images_public_tableView_name_bg.png";//tableview

static char IMG_PUBLIC_PLUS[] = "images/public/image_public_plus.png";//加号按钮
static char IMG_PUBLIC_LAYER_TICK[] = "images/public/layer/image_public_layer_tick.png";//加号按钮

static char IMG_PUBLIC_LAYER_ALLNUM_BG[] = "images/public/layer/images_public_allNum_bg.png";//获取路径线
/////////////////////////////////////弹出layer------//////////////////////////////////////////////////////////////////////////////
static char IMG_PUBLIC_LAYER_BG1[] = "images/public/layer/img_public_getLayerBg1.png"; //公用获得物品弹出层
static char IMG_PUBLIC_LAYER_BG2[] = "images/public/layer/img_public_getLayerBg2.png";//层的二级花纹
static char IMG_PUBLIC_LAYER_GETPATH[]="images/public/layer/images_public_getpath.png";//获取路径背景；
static char IMG_PUBLIC_STORYBG[] = "images/public/layer/image_public_storyBg.png";//剧情对话背景
static char IMG_PUBLIC_STORYSPEAKERNAME[] = "images/public/layer/image_public_storySpeaker.png";//剧情对话说话者名字
static char IMG_PUBLIC_LAYER_NAMEBG[] = "images/public/layer/img_public_getLayer_nameBg.png";//获取路径材料名字背景
static char IMG_PUBLIC_LAYER_LINE[] = "images/public/layer/img_public_getLayer_line.png";//获取路径线

static char IMG_PUBLIC_LAYER_BALL[]="images/public/layer/img_public_layer_ball.png";//圆球
static char IMG_PUBLIC_LAYER_TITLEBG[]="images/public/layer/image_public_layer_titlebg.png";//标题底层
static char IMG_PUBLIC_LAYER_NOTICE[]="images/public/layer/img_public_layer_notice.png";//圆球


//img_public_layer_ball
/////////////////////////////////////////--------------特效--------------///////////////////////////////////////////////
static char IMG_PUBLIC_EFFECT[] = "images/commonEffect/%s.ExportJson";//公用特效

//////////////////////////公用图标/////////////////////////////////////////////////////////////////
static char IMG_ICON_PUBLIC_GOLD[]="images/icon/public/image_icon_gold.png";//元宝
static char IMG_ICON_PUBLIC_POWER[]="images/icon/public/image_icon_bodyPower.png";//体力
static char IMG_ICON_PUBLIC_VIM[]="images/icon/public/img_icon_public_vim.png";//精力
static char IMG_ICON_PUBLIC_COIN[]="images/icon/public/image_icon_coin.png";//铜钱
static char IMG_ICON_FIGHTPOWER[]="images/icon/public/img_icon_fightPower.png";
static char IMG_ICON_BLOODBOTTLE[] = "images/icon/public/image_icon_bloodBottle.png";//血瓶
static char IMG_ICON_EXP[] = "images/icon/public/image_icon_Exp.png";//经验
static char IMG_ICON_JUNGONG[] = "images/icon/public/image_icon_jungong.png";//军工
static char IMG_ICON_QIEXIANRUOKE[] = "images/icon/public/image_icon_qxrkToken.png";//求贤若渴令
static char IMG_ICON_LIXIANXIASHI[] = "images/icon/public/image_icon_lxxsToken.png";//礼贤下士令
static char IMG_ICON_WEICAISHIJU[] = "images/icon/public/image_icon_wcsjToken.png";//唯才是举令
static char IMG_ICON_XUNFANGLIN[] = "images/icon/public/image_icon_xunfanglin.png";//寻访令
static char IMG_ICON_FUNCTION[] = "images/icon/function/%s.png";//新功能开启图标
static char IMG_ICON_HONER[] = "images/icon/public/image_icon_honer.png";//荣誉
static char IMG_ICON_HONERMONEY[] = "images/icon/public/image_icon_honerMoney.png";//荣誉货币



//////////////////////////////////模块顶部名字//////////////////////////////////////////////////////////////////////////////////
//static char IMG_PUBLIC_GOTOBATTLE[] = "images/public/moduleName/image_public_gotoBattle.png";//征战-战役
static char IMG_PUBLIC_MINGZHANYI[] = "images/public/moduleName/image_public_mingZhanyi.png";//征战-名战役
static char IMG_PUBLIC_MINGJIANGZHUAN[] = "images/public/moduleName/image_public_mingJiangZhuan.png";//征战-名将传
static char IMG_PUBLIC_SANGUOWUSHUANG[] = "images/public/moduleName/image_public_sangguoWushuang.png";//征战-三国无双
static char IMG_PUBLIC_CAMPAIGN[] = "images/public/moduleName/image_public_campaign.png";//征战
static char IMG_PUBLIC_JUXIAN[] = "images/public/moduleName/image_public_juxian.png";//举贤
static char IMG_PUBLIC_LIBAO[] = "images/public/moduleName/image_public_libao.png";//礼包
static char IMG_PUBLIC_LINEUP[] = "images/public/moduleName/image_public_lineup.png";//阵容
static char IMG_PUBLIC_PAIMAI[] = "images/public/moduleName/image_public_paimai.png";//拍卖
static char IMG_PUBLIC_SHOP[] = "images/public/moduleName/image_public_shop.png";//商城
static char IMG_PUBLIC_VIP[] = "images/public/moduleName/image_public_vip.png";//vip
static char IMG_PUBLIC_RENWU[] = "images/public/moduleName/image_public_renwu.png";//任务
static char IMG_PUBLIC_ARENA[] = "images/public/moduleName/img_public_arena.png";//竞技场




static char IMG_PUBLIC_EQUIP1[] = "images/public/moduleName/image_public_name_equip1.png";//装备列表
static char IMG_PUBLIC_EQUIP2[] = "images/public/moduleName/image_public_name_equip2.png";//装备列表（暗）
static char IMG_PUBLIC_EQUIP3[] = "images/public/moduleName/image_public_name_equip3.png";//所属装备
static char IMG_PUBLIC_HERO[] = "images/public/moduleName/image_public_name_hero.png";//所属武将
static char IMG_PUBLIC_BASE[] = "images/public/moduleName/image_public_name_base.png";//武将基础
//static char IMG_PUBLIC_EXPERIENCEL[] = "images/public/moduleName/image_public_name_experiencel.png";//武将历练
//static char IMG_PUBLIC_LATTER[] = "images/public/moduleName/image_public_name_latter.png";//书信
//static char IMG_PUBLIC_MATERIAL[] = "images/public/moduleName/image_public_name_material.png";//材料
//static char IMG_PUBLIC_PROPERTY[] = "images/public/moduleName/image_public_name_property.png";//属性
static char IMG_PUBLIC_PROPS[] = "images/public/moduleName/image_public_name_props.png";//道具
//static char IMG_PUBLIC_SKILL[] = "images/public/moduleName/image_public_name_skill.png";//技能
//image_public_name_skill.png

//static char IMG_PUBLIC_STRONG3[] = "images/public/moduleName/image_public_name_strong3.png";//所属强化
//static char IMG_PUBLIC_SMELT[] = "images/public/moduleName/image_public_name_smelt.png";//所属熔炼
static char IMG_PUBLIC_GETPATH[] = "images/public/moduleName/image_public_name_getPath.png";//获取途径
static char IMG_PUBLIC_SIGNIN[] = "images/public/moduleName/image_public_signin.png";//签到
static char IMG_PUBLIC_MONEYDRAW[] = "images/public/moduleName/image_public_moneyDraw.png";//招财
static char IMG_PUBLIC_BENEFIT[] = "images/public/moduleName/image_public_benefit.png";//福利
static char IMG_PUBLIC_FIND[] = "images/public/moduleName/image_public_find.png";//寻访
static char IMG_PUBLIC_SEVENDAY[] = "images/public/moduleName/image_public_name_sevenday.png";//寻访
static char IMG_PUBLIC_LUCKY[] = "images/public/moduleName/image_public_lucky.png";//祈福
static char IMG_PUBLIC_YANXI[] = "images/public/moduleName/image_public_yanxi.png";//竞技场

//////-----------------------------------------图片字体-----------------------------------------------///////
static char IMG_PUBLIC_LABEL_ACTIVE1[] = "images/public/label/image_public_btnLabel_active1.png";
static char IMG_PUBLIC_LABEL_ACTIVE2[] = "images/public/label/image_public_btnLabel_active2.png";//活动
static char IMG_PUBLIC_LABEL_FIGHTGO1[] = "images/public/label/image_public_btnLabel_fightGo1.png";
static char IMG_PUBLIC_LABEL_FIGHTGO2[] = "images/public/label/image_public_btnLabel_fightGo2.png";//奇袭
static char IMG_PUBLIC_LABEL_DETAILS1[] = "images/public/label/image_public_label_details1.png";//详情
static char IMG_PUBLIC_LABEL_DETAILS2[] = "images/public/label/image_public_label_details2.png";//详情
static char IMG_PUBLIC_LABEL_STATS1[] = "images/public/label/image_public_label_stats1.png";
static char IMG_PUBLIC_LABEL_STATS2[] = "images/public/label/image_public_label_stats2.png";//统计
static char IMG_PUBLIC_LABEL_ORDERNAME[] = "images/public/label/image_public_label_orderName.png";//排名
static char IMG_PUBLIC_LABEL_FIGHT[] = "images/public/label/image_public_label_fight.png";//战斗
static char IMG_PUBLIC_LABEL_ZHAOMU[] = "images/public/label/image_famouse_zhaomu.png";//去招募
static char IMG_PUBLIC_LABEL_DELAYTITLE[] = "images/public/label/image_famouse_delayTitle.png";//稍后
static char IMG_PUBLIC_LABEL_SKIPLABEL[] = "images/public/label/image_public_skipLabel.png";//视频跳过

static char IMG_PUBLIC_LABEL_SEEOTHER[] = "images/public/label/image_famouse_seeOther.png";//查看对方
static char IMG_PUBLIC_LABEL_MYRANK[] = "images/public/label/image_famouse_myRank.png";//我的排名

static char IMG_PUBLIC_LABEL_RESET[] = "images/public/label/image_public_label_reset.png";//重置

static char IMG_PUBLIC_LABEL_MAXQUALITY[] = "images/public/label/image_pulbic_label_maxQuality.png";//最高品质
static char IMG_PUBLIC_LABEL_MAX[] = "images/public/label/image_pulbic_label_max.png";//MAX字
static char IMG_PUBLIC_LABEL_EXCHANGE[] = "images/public/label/image_public_labe_exchange.png";//兑换
static char IMG_PUBLIC_LABEL_CDKEY[] = "images/public/label/image_public_labe_cdkey.png";//激活码
static char IMG_PUBLIC_LABEL_EXCHANGEGIFT[] = "images/public/label/image_public_labe_exchangeGift.png";//兑换礼包
static char IMG_PUBLIC_LABEL_AWAKEN[] = "images/public/label/image_public_label_awaken.png";//觉醒字体
static char IMG_PUBLIC_LABEL_INTENSIFY[] = "images/public/label/image_public_label_intensify.png";//btn强化字体
static char IMG_PUBLIC_LABEL_ONEKEYINTENSIFY[] = "images/public/label/image_pulbic_label_oneKeyIntensify.png";//btn一键强化字体

static char IMG_PUBLIC_LABEL_PRACTICE[] = "images/public/label/image_public_label_practice.png";//btn熔炼字体
static char IMG_PUBLIC_LABEL_AUTOADD[] = "images/public/label/image_pulbic_label_autoAdd.png";//自动添加
static char IMG_PUBLIC_LABEL_SMELTING[] = "images/public/label/image_pulbic_label_smelting.png";//可熔炼

static char IMG_PUBLIC_LABEL_EQUIP[] = "images/public/label/image_pulbic_label_equipment.png";//装备字体
static char IMG_PUBLIC_LABEL_SKILL_NUM[] = "images/public/label/image_public_label_num%s.png";//技能名称
static char IMG_PUBLIC_LABEL_GENERAL_VER[] = "images/public/label/image_public_labe_general_ver.png";//武将
static char IMG_PUBLIC_LABEL_BUYWORD[] = "images/public/label/image_public_labe_buyWord.png";//购买字体
static char IMG_PUBLIC_LABEL_HEROFRAMENT[] = "images/public/label/image_famouse_heroFragment.png";//武将碎片
static char IMG_PUBLIC_LABEL_CAILIAOTAG[] = "images/public/label/image_famouse_cailiaoTag.png";//材料觉醒
static char IMG_PUBLIC_LABEL_ITEMDETAILS[] = "images/public/label/image_famouse_Itemdetails.png";//道具详情

static char IMG_MARKET_AUCTION_SELLWORD[] = "images/public/label/image_market_aucton_sellWord.png";//出售
static char IMG_PUBLIC_LABEL_CROSS[] = "images/public/label/image_public_label_cross.png";//穿戴
static char IMG_PUBLIC_LABEL_DOWN[] = "images/public/label/image_public_label_down.png";//御下
static char IMG_PUBLIC_LABEL_NO_CROSS[] = "images/public/label/image_public_label_no_cross.png";//穿戴
static char IMG_PUBLIC_LABEL_CROSSING[] = "images/public/label/image_public_label_crossing.png";//穿戴

static char IMG_PUBLIC_LABEL_SHOP_SELLOUT[] = "images/public/label/image_market_shop_sellout.png";//售罄
static char IMG_PUBLIC_LABEL_SHOP_BLACKSHOP[] = "images/public/label/image_market_blackshop.png";//黑市标题头

static char IMG_PUBLIC_LABEL_BASE_HOR[] = "images/public/label/image_public_labe_base_hor.png";//基础
static char IMG_PUBLIC_LABEL_AWAKE_HOR[] = "images/public/label/image_public_label_awake_hor.png";//觉醒横
static char IMG_PUBLIC_LABEL_EXPERIENCE_HOR[] = "images/public/label/image_public_labe_experience_hor.png";//历练
static char IMG_PUBLIC_LABEL_PROPERTY_HOR[] = "images/public/label/image_public_labe_property_hor.png";//属性
static char IMG_PUBLIC_LABEL_SKILL_HOR[] = "images/public/label/image_public_labe_skill_hor.png";//技能
static char IMG_PUBLIC_LABEL_INTENSIFY_HOR[] = "images/public/label/image_public_label_intensify_hor.png";//强化
static char IMG_PUBLIC_LABEL_PRACTICE_HOR[] = "images/public/label/image_public_label_practice_hor.png";//熔炼

static char IMG_PUBLIC_LABEL_INTENSIFY_VER[] = "images/public/label/image_public_label_intensify_ver.png";//强化竖立
static char IMG_PUBLIC_LABEL_PRACTICE_VER[] = "images/public/label/image_public_label_practice_ver.png";//熔炼竖立
static char IMG_PUBLIC_LABEL_PROPERTY_VER[] = "images/public/label/image_public_labe_property_ver.png";//属性竖立
//static char IMG_PUBLIC_LABEL_AWAKE_VER[] = "images/public/label/image_public_label_awake_ver.png";//觉醒竖立
static char IMG_PUBLIC_LABEL_LETTER_VER[] = "images/public/label/image_public_labe_letter_ver.png";//书信竖立
static char IMG_PUBLIC_LABEL_PROP_VER[] = "images/public/label/image_public_labe_prop_ver.png";//道具竖立
static char IMG_PUBLIC_LABEL_BASE_VER[] = "images/public/label/image_public_labe_base_ver.png";//基础竖立
static char IMG_PUBLIC_LABEL_BASE_SUCCEED[] = "images/public/label/image_public_labe_base_succeed.png";//已完成

static char IMG_PUBLIC_LABEL_LEVEL[] = "images/public/label/image_public_labe_level.png";//等级优先
static char IMG_PUBLIC_LABEL_LEVEL1[] = "images/public/label/image_public_labe_level1.png";//等级优先选中
static char IMG_PUBLIC_LABEL_QUALITY[] = "images/public/label/image_public_labe_quality.png";//品质优先
static char IMG_PUBLIC_LABEL_QUALITY1[] = "images/public/label/image_public_labe_quality1.png";//品质优先选中
static char IMG_PUBLIC_LABEL_PRESTIGE[] = "images/public/label/image_public_labe_prestige.png";//声望优先
static char IMG_PUBLIC_LABEL_PRESTIGE1[] = "images/public/label/image_public_labe_prestige1.png";//声望优先选中
static char IMG_PUBLIC_LABEL_EQUIPMENT[] = "images/public/label/image_public_labe_equip.png";//穿戴优先
static char IMG_PUBLIC_LABEL_EQUIPMENT1[] = "images/public/label/image_public_labe_equip1.png";//穿戴优先选中
static char IMG_PUBLIC_LABEL_BOX[] = "images/public/label/image_public_labe_box.png";//宝箱优先
static char IMG_PUBLIC_LABEL_BOX1[] = "images/public/label/image_public_labe_box1.png";//宝箱优先选中
static char IMG_PUBLIC_LABEL_DRUG[] = "images/public/label/image_public_labe_drug.png";//丹药优先
static char IMG_PUBLIC_LABEL_DRUG1[] = "images/public/label/image_public_labe_drug1.png";//丹药优先优先
static char IMG_PUBLIC_LABEL_NAMEFIRST1[] = "images/public/label/image_public_label_nameFirst1.png";//名字优先
static char IMG_PUBLIC_LABEL_NAMEFIRST2[] = "images/public/label/image_public_label_nameFirst2.png";//名字优先
static char IMG_PUBLIC_LABEL_BFIRST1[] = "images/public/label/image_public_label_bFirst1.png";//B格优先
static char IMG_PUBLIC_LABEL_BFIRST2[] = "images/public/label/image_public_label_bFirst2.png";//B格优先
static char IMG_PUBLIC_LABEL_SUPPORTLABEL[] = "images/public/label/image_public_label_supportLabel.png";//请求支援
static char IMG_PUBLIC_LABEL_LEVELWORD[] = "images/public/label/image_public_label_level.png";//等级


static char IMG_PUBLIC_LABEL_SKILL_VER[] = "images/public/label/image_public_labe_skill_ver.png";//技能竖立
static char IMG_PUBLIC_LABEL_EXPERIENCE_VER[] = "images/public/label/image_public_labe_experience_ver.png";//历练竖立
static char IMG_PUBLIC_LABEL_STUFF_VER[] = "images/public/label/image_public_labe_stuff_ver.png";//材料竖立
static char IMG_PUBLIC_LABEL_DETERMINE[]="images/public/label/image_public_labe_determine.png";
static char IMG_PUBLIC_LABEL_GIFTS[]="images/public/label/image_public_label_gifts.png";//送礼1
static char IMG_PUBLIC_LABEL_GIFTS2[]="images/public/label/image_public_label_gifts2.png";//送礼2
static char IMG_PUBLIC_LABEL_GIVELETTERS[]="images/public/label/image_public_label_giveLetters.png";//送信
static char IMG_PUBLIC_LABEL_DEYAMA[]="images/public/label/image_public_label_deyama.png";//出山
static char IMG_PUBLIC_LABEL_GAIN[]="images/public/label/image_public_label_gain.png";//获取
static char IMG_PUBLIC_LABEL_EQUIP_VER[]="images/public/label/image_public_labe_equip_ver.png";//装备
//image_public_label_currentNum
static char IMG_PUBLIC_LABEL_CURRENTNUM[] = "images/public/label/image_public_label_currentNum.png";//当前数量；
//
static char IMG_PUBLIC_LABEL_STARTPRACTICE[]="images/public/label/image_public_label_startPractice.png";//开始历练
static char IMG_PUBLIC_LABEL_SELLTITLE[]="images/public/label/image_public_labe_selltitle.png";//出售title
static char IMG_PUBLIC_LABEL_GAINCOIN[]="images/public/label/image_public_labe_gainCoin.png";//出售title
static char IMG_PUBLIC_LABEL_TEQUANLIBAO[]="images/public/label/image_public_tequanlibao.png";//特权礼包
static char IMG_PUBLIC_LABEL_GOUMAILIBAO[]="images/public/label/image_public_goumailibao.png";//购买礼包


//
//公告
static char IMG_PUBLIC_LABEL_NOTICE[]="images/public/label/image_pulbic_label_notice.png";
//准奏
static char IMG_PUBLIC_LABEL_CAN[]="images/public/label/image_pulbic_label_can.png";
//出售
static char IMG_PUBLIC_LABEL_SELL[]="images/public/label/image_pulbic_label_sell.png";//装备

static char IMG_PUBLIC_LABEL_HERONAME[]="images/public/label/image_public_label_heroName.png";//武将名称
//使用
static char IMG_PUBLIC_LABEL_USE[] = "images/public/label/image_pulbic_label_use.png";
//今日次数
static char IMG_PUBLIC_LABEL_DAYNUM[] = "images/public/label/image_pulbic_label_dayNum.png";
//剩余数量
static char IMG_PUBLIC_LABEL_SURPLUS[] = "images/public/label/image_pulbic_label_surplus.png";
//装备总数
static char IMG_PUBLIC_LABEL_ALLEQUIP[] = "images/public/label/image_pulbic_label_allEquip.png";
//武将总数
static char IMG_PUBLIC_LABEL_ALLHERO[] = "images/public/label/image_pulbic_label_allHero.png";
//道具名称
static char IMG_PUBLIC_LABEL_PROPSNAME[] = "images/public/label/image_pulbic_label_propsName.png";
//道具总数
static char IMG_PUBLIC_LABEL_ALLPROPS[] = "images/public/label/image_pulbic_label_allProps.png";
//书信总数
static char IMG_PUBLIC_LABEL_ALLLETTER[] = "images/public/label/image_pulbic_label_allLetter.png";
//材料总数
static char IMG_PUBLIC_LABEL_ALLMATERIAL[] = "images/public/label/image_public_label_allMaterial.png";
//材料名称
static char IMG_PUBLIC_LABEL_MATERIALNAME[] = "images/public/label/image_public_label_materialName.png";
//合成
static char IMG_PUBLIC_LABEL_COMPOUND[] = "images/public/label/image_public_label_compound.png";
//去获取
static char IMG_PUBLIC_LABEL_GOTOGAIN[] = "images/public/label/image_public_label_gotoGain.png";


static char IMG_PUBLIC_LABEL_STRONGRESULT[]="images/public/label/image_pulbic_label_strongResult.png";//强化结果
static char IMG_PUBLIC_LABEL_SMELTRESULT[]="images/public/label/image_pulbic_label_smeltResult.png";//熔炼结果

static char IMG_PUBLIC_LABEL_JINJIWORD[] = "images/public/label/image_public_label_jinjiWord.png";//进击

static char IMG_PUBLIC_LABEL_SIGNIN[] = "images/public/label/image_pulbic_label_signin.png";//签

static char IMG_PUBLIC_LABEL_EVERYDAY[] = "images/public/label/image_pulbic_label_everyday.png";//每日签到

static char IMG_PUBLIC_LABEL_LUXURY[] = "images/public/label/image_pulbic_label_luxury.png";//豪华签到


static char IMG_PUBLIC_LABEL_DAYBENEFIT[] = "images/public/label/image_public_labe_dayBenefit.png";//每日福利

static char IMG_PUBLIC_LABEL_WEEKBENEFIT[] = "images/public/label/image_public_labe_weekBenefit.png";//每周福利


static char IMG_PUBLIC_LABEL_WEEKBENEFITUN[] = "images/public/label/image_public_labe_weekBenefitun.png";//每周福利没选中
static char IMG_PUBLIC_LABEL_WEEKBENEFITCHSOE[] = "images/public/label/image_public_labe_weekBenefitchose.png";//每周福利选中
static char IMG_PUBLIC_LABEL_DAYBENEFITUN[] = "images/public/label/image_public_labe_dayBenefitun.png";//每日福利没选中
static char IMG_PUBLIC_LABEL_DAYBENEFITCHOSE[] = "images/public/label/image_public_labe_dayBenefitchose.png";//每日福利选中



static char IMG_PUBLIC_LABEL_DRAW[] = "images/public/label/image_public_labe_draw.png";//领取

static char IMG_PUBLIC_LABEL_ISLINGQU[] = "images/public/label/image_public_labe_week_islingqu.png";//已领取


static char IMG_PUBLIC_LABEL_RECHARGE[] = "images/public/label/image_pulbic_label_recharge.png";//充值

static char IMG_PUBLIC_LABEL_SEVENBEN[] = "images/public/label/image_public_labe_sevenBen.png";//七日福利

static char IMG_PUBLIC_LABEL_HALFPAY[] = "images/public/label/image_public_labe_halfpay.png";//半价抢购

static char IMG_PUBLIC_LABEL_PAIMAIUSO[] = "images/public/label/image_public_labe_paimaisuo.png";//拍卖所

static char IMG_PUBLIC_LABEL_PAIMAIUSO1[] = "images/public/label/image_public_labe_paimaisuo1.png";//

static char IMG_PUBLIC_LABEL_QUCHUSAO[] = "images/public/label/image_public_labe_quchusao.png";//去出售

static char IMG_PUBLIC_LABEL_QUCHUSAO1[] = "images/public/label/image_public_labe_quchusao1.png";//

static char IMG_PUBLIC_LABEL_SAHNGJIA[] = "images/public/label/image_public_labe_shangjia.png";//上架中

static char IMG_PUBLIC_LABEL_SAHNGJIA1[] = "images/public/label/image_public_labe_shangjia1.png";//



//
//////////////////////////////技能相关//////////////////////////////////////////////////////////

//static char IMG_SKILL_EFFECT[] = "images/skill/effect/%s.ExportJson";
static char IMG_SKILL_EFFECT[] = "images/skill/effect/%s.ExportJson";
static char IMG_SKILL_ICON[] = "images/skill/icon/%s.png";
static char IMG_BUFF_ICON[] = "images/skill/buff/%s.png";
static char IMG_SKILL_SKILLNAME[] = "images/skill/skillName/%s.png";
static char IMG_SKILL_ANGRYICON[] = "images/skill/icon/angry.png";
static char IMG_SKILL_FORM[] = "images/public/image_public_skillForm.png";
static char IMG_BUFF_FORM[] = "images/public/image_public_buffForm.png";
/////////////////////////////新手引导////////////////////////////////////////////////////////////////////////////////////////////////////
static char IMG_NEWGUIDE_TALKBG[] = "images/newGuide/img_newGuide_bg.png";
static char IMG_NEWGUIDE_ARROW[] = "images/newGuide/image_newGuide_arrow.png";
static char IMG_NEWGUIDE_ARROW1[] = "images/newGuide/image_newGuide_arrow1.png";
//static char IMG_NEWGUIDE_HAND[] = "images/newGuide/img_newGuide_hand.png";
static char IMG_NEWGUIDE_EFFECT[] = "images/newGuide/%s.ExportJson";
static char IMG_NEWGUIDE_FIRSTGAME[] = "images/newGuide/image_newguide_firstGame.png";
//////////公用loading//////////////////////////////////////////////////////////////////////////////
//static char IMG_PUBLIC_LOADING[] = "images/public/loading/image_public_loading.png";//
//static char IMG_PUBLIC_LOADINGPERSON[] = "images/public/loading/image_public_loadingPerson.png";
//static char IMG_PUBLIC_LOADINGPROGRESSBG[] = "images/public/loading/image_public_loadingProgressBg.png";
//static char IMG_PUBLIC_LOADINGPROGRESSBG1[] = "images/public/loading/image_public_loadingProgressBg1.png";
//static char IMG_PUBLIC_LOADINGPROGRESS[] = "images/public/loading/image_public_loadingProgress.png";
//static char IMG_PUBLIC_LOADINGPERSON_FORM[] = "images/public/loading/image_public_loadingPersonForm.png";
//static char IMG_PUBLIC_LOADINGPERSON_BG[] = "images/public/loading/image_public_loadingPersonBg.png";

static char IMG_PUBLIC_LOADINGDOT[] = "images/public/loading/image_public_loadingDot.png";
static char IMG_PUBLIC_CONNECTING[] = "images/public/loading/image_public_conntecting.png";
static char IMG_PUBLIC_LOADING_EFFECT[] = "images/public/loading/loading.ExportJson";
static char IMG_PUBLIC_LOADING_CIRCLEBG[] = "images/public/loading/image_public_loading_circleBg.png";//loading背景
static char IMG_PUBLIC_LOADING_CIRCLEMASK[] = "images/public/loading/image_public_loading_circleMask.png";//loaadig进度条
static char IMG_PUBLIC_LOADING_TEXT[] = "images/public/loading/image_public_loading_text/%s.png";
/////---------------------------------------------------人物info（userHead）----------------------//
static char IMG_USERHEAD_HEADBG[]="images/userHead/img_userHead_bg.png";
static char IMG_USERHEAD_SETTING[]="images/userHead/img_userHead_setting.png";
//img_userHead_setting.png
static char IMG_USERHEAD_POWER[]="images/userHead/img_userHead_power.png";//战力
static char IMG_USERHEAD_HEADBOX[]="images/userHead/img_userHead_headBox.png";
static char IMG_USERHEAD_LVBG[]="images/userHead/img_userHead_lvBg.png";
static char IMG_USERHEAD_NUMBG[]="images/userHead/img_userHead_numBg.png";
static char IMG_USERHEAD_NUMBG2[]="images/userHead/img_userHead_numBg2.png";
static char IMG_USERHEAD_HEADLITTLEBG[]="images/userHead/img_userHead_headbg.png";//头像北京

static char IMG_USERHEAD_PROGRESS[]="images/userHead/img_userHead_progress.png";

static char IMG_USERHEAD_VIP_BTN[]="images/userHead/img_userHead_vip_btn.png";


//------------------------------------------------主界面---------------------------------------------//

static char IMG_HOMEUI_MAIN001BG[]="images/battle/battlescene/main001_far.tmx";
static char IMG_HOMEUI_001MID[]="images/battle/battlescene/main001_mid.tmx";
static char IMG_HOMEUI_001NEAR[]="images/battle/battlescene/main001_near.tmx";
static char IMG_HOMEUI_001CLOSE[]="images/battle/battlescene/main001_close.tmx";


static char IMG_HOMMEUI_ACTIVEBG[] = "images/homeUI/image_homeUI_activeBg.png";// 底层
static char IMG_HOMMEUI_ACTIVEFRONT[] = "images/homeUI/image_homeUI_activeFront.png";//上层
static char IMG_HOMMEUI_ACTIVEIMAGE[] = "images/homeUI/image_homeUI_activeImage1.png";//中层
//------------------------------------战斗界面---------------------------------------------//


static string IMG_BATTLE_BATTLESCENE_PATH = IMG_PRE + "battle/battlescene/";
static string IMG_BATTLE_NEARMAP = IMG_PRE + "battle/battlescene/%s_near.tmx";
static string IMG_BATTLE_CLOSEMAP = IMG_PRE + "battle/battlescene/%s_close.tmx";
static string IMG_BATTLE_MIDMAP = IMG_PRE + "battle/battlescene/%s_mid.tmx";



static char IMG_BATTLE_ATTACK[]="images/battle/image_battle_attack.png";
static char IMG_BATTLE_BTNBG[] = "images/battle/image_battle_btnBg.png";
static char IMG_BATTLE_BIGSKILLBG[] = "images/battle/image_battle_bigSkillBg.png";
static char IMG_BATTLE_DOUBLEHIT[] = "images/battle/image_battle_doubleHit.png";// 连击
static char IMG_BATTLE_MAPBG[] = "images/battle/battlescene/background/%s.png";


static char IMG_BATTLE_JUMPBTN[] = "images/battle/image_battle_jump.png";//跳跃
static char IMG_BATTLE_ANGRYPROGRESS[] = "images/battle/image_battle_angryProgress.png";//怒气进度条
static char IMG_BATTLE_ANGRYPROGRESSBG[] = "images/battle/image_battle_angryProgressBg.png";//怒气进度条背景
static char IMG_BATTLE_GO[] = "images/battle/image_battle_go.png";
static char IMG_BATTLE_HURTNUM[] = "images/battle/hurtImage/%d.png";
static char IMG_BATTLE_HURTMINUS[] = "images/battle/hurtImage/image_minus.png";

static char IMG_BATTLE_CRIT[] = "images/battle/image_battle_crit.png";//暴击
static char IMG_BATTLE_BLOCK[] = "images/battle/image_battle_block.png";//格档
static char IMG_BATTLE_BOTTLEBG[] = "images/battle/image_battle_bottleBg.png";

static char IMG_BATTLE_HEROBLOODBG[] = "images/battle/image_battle_heroBloodBg.png";//英雄血条背景
static char IMG_BATTLE_HEROBLOOD[] = "images/battle/image_battle_heroBlood.png";//英雄血条
static char IMG_BATTLE_HEROHEADBLOOD[] = "images/battle/img_battle_heroHeadBlood.png";//英雄头像血条
static char IMG_BATTLE_HEROHEADBLOODBG[] = "images/battle/img_battle_heroHeadBloodBg.png";
static char IMG_BATTLE_BATTLENAME[] = "images/battle/image_battle_stageNameBg.png";//名字背景
static char IMG_BATTLE_TIMEBG[] = "images/battle/image_battle_timeBg.png";//时间背景

static char IMG_BATTLE_PROGRESSBG[] = "images/battle/image_battle_progressBg.png";//进度条背景
static char IMG_BATTLE_PROGRESS[] = "images/battle/image_battle_progress.png";//进度条背景
static char IMG_BATTLE_PROGRESSFRONT[] = "images/battle/image_battle_progressFront.png";//进度条
static char IMG_BATTLE_PROGRESSHAT[] = "images/battle/image_battle_progressHat.png";//进度帽子
static char IMG_BATTLE_PROGRESSDOT[] = "images/battle/image_battle_progressDot.png";

static char IMG_BATTLE_BOSSBLOODFORM[] = "images/battle/image_battle_bossBloodForm.png";//
static char IMG_BATTLE_BOSSBLOODBG[] = "images/battle/image_battle_bossBloodBg.png";
static char IMG_BATTLE_BOSSBLOOD[] = "images/battle/image_battle_bossBlood.png";
static char IMG_BATTLE_CONTINUE[] = "images/battle/image_battle_continue.png";//是否继续


static char IMG_BATTLE_PLAY[] = "images/battle/image_battle_play.png";///继续游戏
static char IMG_BATTLE_BACK[] = "images/battle/image_battle_back.png";//退出战场
static char IMG_BATTLE_PAUSE[] = "images/battle/image_battle_pause.png";//暂停游戏
static char IMG_BATTLE_AUTOFIGHTBTN[] = "images/battle/image_battle_autoBtn.png";//自动战斗
static char IMG_BATTLE_UNAUTOFIGHTBTN[] = "images/battle/image_battle_unAutoBtn.png";//手动战斗
static char IMG_BATTLE_ATTRIBINFO[] = "images/battle/attribInfo/%s.png";//属性加减

////----------------------------------------------扫荡-----------------------------------------------------------------
static char IMG_BATTLERAIDS_COMPLETED[] = "images/battleRaids/image_battleRaids_raidsCompleted.png";//扫荡完成
static char IMG_BATTLERAIDS_DRUM[] = "images/battleRaids/image_battleRaids_drum.png";//小鼓
static char IMG_BATTLERAIDS_ITEMBG[] = "images/battleRaids/image_battleRaids_itemBg.png";//扫荡结果背景
static char IMG_BATTLERAIDS_TITLE[] = "images/battleRaids/image_battleRaids_title.png";//扫荡结果标题
//--------------------------------------------战斗结果----------------------------------------------------
static char IMG_BATTLERESULT_USERPRIZEBG[] = "images/battleResult/winLayer/image_battleResult_userPrizeBg.png";
static char IMG_BATTLERESULT_ITEMBG[] = "images/battleResult/winLayer/image_battleResult_iitemBg.png";
static char IMG_BATTLERESULT_REPLAYBTN[] = "images/battleResult/winLayer/image_battleResult_rePlayBtn.png";//重播

static char IMG_BATTLERESULT_FLOWER[] = "images/battleResult/winLayer/image_battleResult_flower.png";//麦穗
static char IMG_BATTLERESULT_WINTITLE[] = "images/battleResult/winLayer/image_battleResult_winTitle.png";//胜利标题
static char IMG_BATTLERESULT_STAR[] = "images/battleResult/winLayer/image_battleResult_star.png";
static char IMG_BATTLERESULT_STARBG[] = "images/battleResult/winLayer/image_battleResult_starBg.png";//

static char IMG_BATTLERESULT_ENDBTN[] = "images/battleResult/image_battleResult_endBtn.png";//结束按钮
static char IMG_BATTLERESULT_AGAINBTN[] = "images/battleResult/image_battleResult_againBtn.png";//再战
static char IMG_BATTLERESULT_LOSEBG[] = "images/battleResult/image_battle_loseBg.png";//失败背景
static char IMG_BATTLERESULT_LOSETITLE[] = "images/battleResult/image_battle_loseTitle.png";//失败标题
static char IMG_BATTLERESULT_ITEMLABEL[] = "images/battleResult/image_battle_itemlabel%s.png";//cell
static char IMG_BATTLERESULT_LOSTWORD[] = "images/battleResult/image_battle_loseWord.png";//失败字



//------------------------------------关卡界面---------------------------------------------//

static char IMG_STAGE_LISTBG[] = "images/stage/stageBg/image_stage_bg%s.png";
//static char IMG_STAGE_LISTNAME[] = "images/stage/stageBg/image_stage_name%s.png";
//static char IMG_STAGE_DESCRIPT[] = "images/stage/stageBg/image_stage_des%s.png";//关卡描述
static char IMG_STAGE_ITEMBG[] = "images/stage/image_stage_itemBg.png";
static char IMG_STAGE_ITEMFRONT[] = "images/stage/image_stage_itemFront.png";
static char IMG_STAGE_ITEMLOCK[] = "images/stage/image_stage_lock.png";

static char IMG_STAGE_PARTICLE[] = "images/stage/image_stage_particle.png";

static char IMG_STAGE_CTGWORD[] = "images/stage/image_stage_ctgWord.png";
static char IMG_STAGE_CTGBG[] = "images/stage/image_stage_ctgBg.png";
static char IMG_STAGE_RIGHTBTN[] = "images/stage/image_stage_rightBtn.png";
static char IMG_STAGE_MZYWORD[] = "images/stage/image_stage_mzyWord.png";
static char IMG_STAGE_MZYBG[] = "images/stage/image_stage_mzyBg.png";

//---------------------------------关卡章节-------------------------------------------------------
static char IMG_CHAPTER_DIWORD[] = "images/chapter/image_chapter_diWord.png";  //第
static char IMG_CHAPTER_CHAPTERWORD[] = "images/chapter/image_chapter_chapterWord.png";//章
static char IMG_CHAPTER_STARPROGRESSBG[] = "images/chapter/image_chapter_starrogressBg.png";//boss 宝箱进度
static char IMG_CHAPTER_STARPROGRESS[] = "images/chapter/image_chapter_starrogress.png";//boss 宝箱进度
static char IMG_CHAPTER_COMMONWORD[] = "images/chapter/image_chapter_commonWord.png";//普通文字
static char IMG_CHAPTER_BESTWORD[] = "images/chapter/image_chapter_bestWord.png";//o精英文字
static char IMG_CHAPTER_STAGENAMEBG[] = "images/chapter/image_chapter_stageNameBg.png";//关卡名字背包
//static char IMG_CHAPTER_STAGEFORM[] = "images/chapter/image_chapter_stageForm.png";
static char IMG_CHAPTER_STAGEFORM[] = "images/chapter/guankadituxuanzhong/guankadituxuanzhong.ExportJson";

static char IMG_CHAPTER_BGPATH[] = "images/chapter/chapterBg/%s.png";//章节背景资源
static char IMG_CHAPTER_BGPATHJPG[] = "images/chapter/chapterBg/%s.jpg";//章节背景资源
static char IMG_CHAPTER_BESTBTNEFFECT[] = "images/chapter/jingyingdikuang/jingyingdikuang.ExportJson";//精英选择框
static char IMG_CHAPTER_COMMONBTNEFFECT[] = "images/chapter/putongxuanzhongkuang/putongxuanzhongkuang.ExportJson";//普通选择框

//-----------------------------------------阵容界面-----------------------------------------//
static char IMG_LINEUP_CHEERBG[] = "images/lineup/image_lineup_cheerBg.png";
static char IMG_LINEUP_FIGHTBG[] = "images/lineup/image_lineup_fightBg.png";
static char IMG_LINEUP_HEAD[] = "images/lineup/image_lineup_head.png";

static char IMG_LINEUP_HEROPAR[] = "images/lineup/image_lineup_heroPar.png";
static char IMG_LINEUP_NAMEBG[] = "images/lineup/image_lineup_nameBg.png";
static char IMG_LINEUP_ZJWORD[] = "images/lineup/image_lineup_zjWord.png";
static char IMG_LINEUP_FJWORD[] = "images/lineup/image_lineup_fjWord.png";
static char IMG_LINEUP_BG[] = "images/lineup/image_lineup_bg.jpg";
static char IMG_LINEUP_HEADBG[] = "images/lineup/image_lineup_headBg.png";
static char IMG_LINEUP_HEROBTN[] = "images/lineup/image_lineup_heroBtn.png";
static char IMG_LINEUP_UNGRAYHERO[] = "images/lineup/image_lineup_unGrayHero.png";
static char IMG_LINEUP_PARTICLE[] = "images/lineup/image_lineup_particle.plist";
static char IMG_LINEUP_ZHENRONGWORD[] = "images/lineup/image_lineup_zhenrongWord.png";
static char IMG_LINEUP_LINGDAOLIBG[] = "images/lineup/image_lineup_lingdaoliBg.png";
static char IMG_LINEUP_ZHANLILIBG[] = "images/lineup/image_lineup_zhanliBg.png";
static char IMG_LINEUP_SHANGZHENBG[] = "images/lineup/image_lineup_shangzhenBg.png";
static char IMG_LINEUP_SHANGZHEN1[] = "images/lineup/image_lineup_shangzhen1.png";
static char IMG_LINEUP_SHANGZHEN2[] = "images/lineup/image_lineup_shangzhen2.png";
static char IMG_LINEUP_XIAZHEN[] = "images/lineup/image_lineup_xiazhen.png";
static char IMG_LINEUP_STAR[] = "images/lineup/image_lineup_star.png";
static char IMG_LINEUP_ZENGJIA[] = "images/lineup/image_lineup_zengjia.png";
static char IMG_LINEUP_BUY[] = "images/lineup/image_lineup_buy.png";
static char IMG_LINEUP_YISHANGZHEN[] = "images/lineup/image_lineup_yishangzhen.png";
static char IMG_LINEUP_YISHANGZHENWORD[] = "images/lineup/image_lineup_yishangzhenWord.png";
static char IMG_LINEUP_HEROWAIT[] = "images/lineup/image_lineup_heroWait.png";
static char IMG_LINEUP_HEROWAITWORD[] = "images/lineup/image_lineup_heroWaitword.png";
static char IMG_LINEUP_HEADPICBG[] = "images/lineup/image_lineup_headPicBg.png";
static char IMG_LINEUP_ADDHERO[] = "images/lineup/image_lineup_addHero.png";//添加英雄
static char IMG_LINEUP_HEROBTNWORD[] = "images/lineup/image_lineup_heroBtnWord.png";//出战字
static char IMG_LINEUP_SAHNGZHEN[] = "images/lineup/image_lineup_shangzhen.png";//上阵
static char IMG_LINEUP_ADD[] = "images/lineup/image_lineup_add.png";//加号





//-----------------------------------------武将列表-----------------------------------------//


static char IMG_GENERALSLIST_PREST[] = "images/generals/generalsList/images_generalsList_prest.png";//列表声望

static char IMG_GENERALSLIST_ARROW[] = "images/generals/generalsList/images_generalsList_arrow.png";//列表展开按钮

static char IMG_GENERALSLIST_SHRINK_BG[] = "images/generals/generalsList/images_generalsList_shrink_bg.png";//收缩背景

static char IMG_GENERALSLIST_BOTTOM_BG[] = "images/generals/generalsList/images_generalsList_bottom_bg.png";//底栏背景




//--------------------------------------------------------武将卡牌-------------------------------------------------------//

static char IMG_GENERALS_CARD_BG[] = "images/generals/generalsCard/image_generals_card_bg.png";//背景
static char IMG_GENERALS_CARD_BG2[] = "images/generals/generalsCard/image_generals_card_bg2.png";//背景
static char IMG_GENERALS_CARD_TEMPCARD[] = "images/generals/generalsCard/image_generals_card_tempCard%d.png";//临时卡牌
static char IMG_GENERALS_CARD_BOX[] = "images/generals/generalsCard/image_generals_card_box.png";//框
static char IMG_GENERALS_CARD_BOX2[] = "images/generals/generalsCard/image_generals_card_box2.png";//框
//static char IMG_GENERALS_CARD_LVBG[] = "images/generals/generalsCard/image_generals_card_lvBg.png";//等级
static char IMG_GENERALS_CARD_PROGRESS[] = "images/generals/generalsCard/image_generals_card_progress.png";//经验
static char IMG_GENERALS_CARD_PROGRESSYELLOW[] = "images/generals/generalsCard/image_generals_card_progressYellow.png";
static char IMG_GENERALS_CARD_PROGRESSBG[] = "images/generals/generalsCard/image_generals_card_progressbg.png";// 进度条底框
static char IMG_GENERALS_CARD_NEWHALFBOX[] = "images/generals/generalsCard/image_generals_card_boxnew.png";// 新半截框
static char IMG_GENERALS_CARD_TITTLEBG[] = "images/generals/generalsCard/image_generals_card_titlebg.png";// 新生命底层
static char IMG_GENERALS_CARD_ALIVE[] = "images/generals/generalsCard/image_generals_card_alive.png";// 生命条
static char IMG_GENERALS_CARD_ATTACT[] = "images/generals/generalsCard/image_generals_card_attack.png";// 攻击
static char IMG_GENERALS_CARD_DEFENT[] = "images/generals/generalsCard/image_generals_card_defent.png";// 防御



//-----------------------------------------武将信息-----------------------------------------//
static char IMG_GENERALS_BG[] = "images/generals/image_generals_bg.png";//背景
static char IMG_GENERALS_AWAKELABEL[] = "images/generals/image_generals_awakeLabel.png";//觉醒字
static char IMG_GENERALS_LEVELUPLABEL[] = "images/generals/image_generals_levelUpLabel.png";//升级字
static char IMG_GENERALS_UpStarLabel[] = "images/generals/image_generals_upStarLabel.png";//升星字
static char IMG_GENERALS_MORELABEL[] = "images/generals/image_generals_moreLabel.png";
//-----------------------------------------武将基础信息-----------------------------------------//
//
static char IMG_GENERALS_AWAKE_BG[] = "images/generals/generalsBase/image_generals_awake_bg.png";//觉醒装备背景

static char IMG_GENERALS_BASE_BG[] = "images/generals/generalsBase/image_generals_base_bg.png";//背景1
static char IMG_GENERALS_BASE_BG2[] = "images/generals/generalsBase/image_generals_base_bg2.png";//背景2
static char IMG_GENERALS_BASE_BGBOX[] = "images/generals/generalsBase/image_generals_base_bgbox.png";//背景框
static char IMG_GENERALS_BASE_TWOBG[] = "images/generals/generalsBase/image_generals_base_twoBg.png";
static char IMG_GENERALS_EQUIPPLUS[] = "images/generals/generalsBase/image_generals_equipplus.png";//装备加号

static char IMG_GENERALS_BASE_EQUIP[] = "images/generals/generalsBase/image_generals_base_equip%s.png";//装备
static char IMG_GENERALS_BASE_BALL1[] = "images/generals/generalsBase/image_generals_base_ball1.png";//圆球1
static char IMG_GENERALS_BASE_BALL2[] = "images/generals/generalsBase/image_generals_base_ball2.png";//圆球2
static char IMG_GENERALS_EQUIP_LIST_LABEL[] = "images/generals/generalsBase/image_generals_base_equip_list_label.png";//装备列表字
static char IMG_GENERALS_EQUIP_LABEL[] = "images/generals/generalsBase/image_generals_base_equip_label.png";//所属装备
static char IMG_GENERALS_EQUIP_DEFAULT[] = "images/generals/generalsBase/image_generals_equipment_default.png";//装备默认地图
static char IMG_GENERALS_EQUIP_CANEQUIP[] = "images/generals/generalsBase/image_generals_base_canEquip.png";//可装备
static char IMG_GENERALS_EQUIP_RANKBG[] = "images/generals/generalsBase/image_generals_base_rankBg.png";//装备小背景
static char IMG_GENERALS_EQUIP_RANKBG2[] = "images/generals/generalsBase/image_generals_base_rankBg2.png";//装备小背景


//新觉醒
static char IMG_AWAKE_BG[] = "images/generals/awake/image_general_awakeBg.png";
static char IMG_AWAKE_CIRCLE[] = "images/generals/awake/image_awake_circle%s.png";
//升星
static char IMG_UPSTAR_BG[] = "images/generals/upStar/image_general_upStarBg.png";
static char IMG_UPSTAR_STARLIGHTBG[] = "images/generals/upStar/image_upStar_starLightBg.png";
static char IMG_UPSTAR_STARFORM[] = "images/generals/upStar/image_upStar_starForm.png";

//-----------------------------------------武将技能信息-----------------------------------------//
static char IMG_GENERALS_SKILL_BG[] = "images/generals/generalsSkill/image_generals_skill_bg.png";//技能背景
static char IMG_GENERALS_SKILL_NUM_BG[] = "images/generals/generalsSkill/image_generals_skill_num_bg.png";//技能名字背景
static char IMG_GENERALS_SKILL_LABEL1[] = "images/generals/generalsSkill/image_generals_skill_label1.png";//技能名字1
static char IMG_GENERALS_SKILL_LABEL2[] = "images/generals/generalsSkill/image_generals_skill_label2.png";//技能名字2
static char IMG_GENERALS_KARMA_LABEL[] = "images/generals/generalsSkill/image_generals_karma_label.png";//缘分

static char IMG_GENERALS_SKILL_CONT_BG[] = "images/generals/generalsSkill/image_generals_skill_cont_bg.png";//单个块背景
static char IMG_GENERALS_SKILL_CONT_LINE[] = "images/generals/generalsSkill/image_generals_skill_cont_line.png";//单个块线

//-----------------------------------------武将历练信息-----------------------------------------//

static char IMG_GENERALS_EXPERIENCE_ARROW[] = "images/generals/generalsExperience/imge_generals_experience_arrow.png";//箭头
static char IMG_GENERALS_EXPERIENCE_TITLE_BG[] = "images/generals/generalsExperience/imge_generals_experience_title_bg.png";//标题背景
static char IMG_GENERALS_EXPERIENCE_RESULT_LABEL[] = "images/generals/generalsExperience/imge_generals_experience_result_label.png";//标题字
static char IMG_GENERALS_EXPERIENCE_MATTER_LABEL[] = "images/generals/generalsExperience/imge_generals_experience_matter_label.png";//历练素材标题字
static char IMG_CHOOSE_CARD_BG[] = "images/generals/generalsExperience/imge_choose_card_bg.png";//选择卡牌背景
static char IMG_CHOOSE_CARD_NUM[] = "images/generals/generalsExperience/imge_choose_card_num%s.png";//选择卡位置

static char IMG_GENERALS_EXPERIENCE_LIST_LABEL[]="images/generals/generalsExperience/imge_choose_list_label.png";
static char IMG_GENERALS_EXPERIENCE_LIST_BG[] = "images/generals/generalsExperience/imge_choose_list_bg.png";
static char IMG_GENERALS_EXPERIENCE_LIST_BG2[] = "images/generals/generalsExperience/imge_choose_list_bg2.png";
static char IMG_GENERALS_EXPERIENCE_BOTTOM_BG[] = "images/generals/generalsExperience/imge_choose_bottom_bg.png";
static char IMG_GENERALS_EXPERIENCE_TOP_BG[] = "images/generals/generalsExperience/imge_choose_top_bg.png";
static char IMG_GENERALS_EXPERIENCE_CARD_NUMBOX[] = "images/generals/generalsExperience/imge_choose_card_numBox.png";
//----------------------------------------书信-----------------------------------------//
//好友度
static char IMG_GENERALS_LATTER_FRIEND[] = "images/generals/generalsLetter/image_generals_latter_friend.png";
//书信列表
static char IMG_GENERALS_LATTER_LABEL[] = "images/generals/generalsLetter/image_generals_latter_label.png";
//书信列表半透明
static char IMG_GENERALS_LATTER_LABEL2[] = "images/generals/generalsLetter/image_generals_latter_label2.png";
//书信数量
static char IMG_GENERALS_LATTER_NUMBER[] = "images/generals/generalsLetter/image_generals_latter_number.png";
//好友进度条
static char IMG_GENERALS_LATTER_PROGRESS[] = "images/generals/generalsLetter/image_generals_latter_progress.png";
//好友进度条背景
static char IMG_GENERALS_LATTER_PROGRESSBG[] = "images/generals/generalsLetter/image_generals_latter_progressBg.png";
//消耗
static char IMG_GENERALS_LATTER_EXPEND[] = "images/generals/generalsLetter/image_generals_latter_expend.png";
//单个列表背景
static char IMG_GENERALS_LATTER_CELLBG[] = "images/generals/generalsLetter/image_generals_latter_cellBg.png";
//letter背景
static char IMG_GENERALS_LATTER_BG[] = "images/generals/generalsLetter/image_generals_latter_bg.png";
//----------------------------------------道具-----------------------------------------//
//描述背景
static char IMG_GENERALS_PROPS_DESC_BG[] = "images/generals/generalsProps/image_generals_props_desc_bg.png";
//道具列表
static char IMG_GENERALS_PROPS_LABEL[] = "images/generals/generalsProps/image_generals_props_label.png";
//道具列表2
static char IMG_GENERALS_PROPS_LABEL2[] = "images/generals/generalsProps/image_generals_props_label2.png";

//image_generals_props_desc.png
//----------------------------------------材料-----------------------------------------//
//材料列表
static char IMG_GENERALS_MATERIAL_LABEL[] = "images/generals/generalsMaterial/image_generals_material_label.png";
static char IMG_GENERALS_MATERIAL_LABEL2[] = "images/generals/generalsMaterial/image_generals_material_label2.png";
//材料数量
static char IMG_GENERALS_MATERIAL_NUMBER[] = "images/generals/generalsMaterial/image_generals_material_number.png";
//材料进度条
static char IMG_GENERALS_MATERIAL_PROGRESS[] = "images/generals/generalsMaterial/image_generals_material_progress.png";
//材料进度条背景
static char IMG_GENERALS_MATERIAL_PROGRESSBG[] = "images/generals/generalsMaterial/image_generals_material_progressBg.png";
//-----------------------------------------武将属性信息-----------------------------------------//
static char IMG_GENERALS_PROPERTY_TITLE_BG[] = "images/generals/generalsProperty/image_generals_property_title_bg.png";//标题背景
static char IMG_GENERALS_PROPERTY_RES_LABEL[] = "images/generals/generalsProperty/image_generals_property_res_label.png";//抗性字
static char IMG_GENERALS_PROPERTY_PROB_LABEL[] = "images/generals/generalsProperty/image_generals_property_prob_label.png";//概率属性字
static char IMG_GENERALS_PROPERTY_BASE_LABEL[] = "images/generals/generalsProperty/image_generals_property_base_label.png";//基础属性字

//-----------------------------------------装备强化-----------------------------------------//
static char IMG_GENERALS_EQUIP_BG[] = "images/generals/generalsEquip/image_generals_equip_bg.png";
static char IMG_GENERALS_EQUIP_PROGRESS[] = "images/generals/generalsEquip/image_generals_equip_progress.png";//进度条
static char IMG_GENERALS_EQUIP_PROGRESSBG[] = "images/generals/generalsEquip/image_generals_equip_progressBg.png";//进度条背景
static char IMG_GENERALS_EQUIP_PROGRESSBGBOX[] = "images/generals/generalsEquip/image_generals_equip_bgbox.png";//背景框


//-----------------------------------------装备熔炼-----------------------------------------//
static char IMG_GENERALS_SMELT_BG[] = "images/generals/generalsEquip/image_generals_smelt_bg.png";
static char IMG_GENERALS_EQUIP_BALL[] = "images/generals/generalsEquip/image_generals_equip_ball.png";
static char IMG_GENERALS_EQUIP_BALL2[] = "images/generals/generalsEquip/image_generals_equip_ball2.png";
static char IMG_GENERALS_SMELT_RESULT[] = "images/generals/generalsEquip/image_generals_smelt_result.png";
static char IMG_GENERALS_STRONG_RESULT[] = "images/generals/generalsEquip/image_generals_strong_result.png";
static char IMG_GENERALS_SMELT_LABEL1[] = "images/generals/generalsEquip/image_generals_smelt_label1.png";
static char IMG_GENERALS_SMELT_LABEL2[] = "images/generals/generalsEquip/image_generals_smelt_label2.png";
//
//-----------------------------------------活动-----------------------------------------//
static char IMG_GENERALS_SEVENACTIVITY_TIME_LABEL[] = "images/activity/sevenActivity/image_sevenActivity_activityTime_label.png";//活动结束时间
static char IMG_GENERALS_SEVENACTIVITY_AWARD_BG[] = "images/activity/sevenActivity/image_sevenActivity_award_bg.png";//奖励背景
static char IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG[] = "images/activity/sevenActivity/image_sevenActivity_award_btnBg.png";//奖励按钮背景
static char IMG_GENERALS_SEVENACTIVITY_BG[] = "images/activity/sevenActivity/image_sevenActivity_bg.png";//七日背景
static char IMG_GENERALS_SEVENACTIVITY_BG2[] = "images/activity/sevenActivity/image_sevenActivity_bg2.png";//七日背景2
static char IMG_GENERALS_SEVENACTIVITY_CASE[] = "images/activity/sevenActivity/image_sevenActivity_case%d.png";//奖励分支
static char IMG_GENERALS_SEVENACTIVITY_JINXING[] = "images/activity/sevenActivity/image_sevenActivity_activityTime_jinxing.png";//进行
static char IMG_GENERALS_SEVENACTIVITY_LINGQU[] = "images/activity/sevenActivity/image_sevenActivity_activityTime_lingqu.png";//领取
static char IMG_GENERALS_SEVENACTIVITY_DAY[] = "images/activity/sevenActivity/image_sevenActivity_day%d.png";//天数
static char IMG_GENERALS_SEVENACTIVITY_DAYBG1[] = "images/activity/sevenActivity/image_sevenActivity_dayBg1.png";//天数背景
static char IMG_GENERALS_SEVENACTIVITY_DAYBG2[] = "images/activity/sevenActivity/image_sevenActivity_dayBg2.png";//天数背景
static char IMG_GENERALS_SEVENACTIVITY_SEVENDAYBG1[] = "images/activity/sevenActivity/image_sevenActivity_sevenDayBg1.png";//天数背景
static char IMG_GENERALS_SEVENACTIVITY_SEVENDAYBG2[] = "images/activity/sevenActivity/image_sevenActivity_sevenDayBg2.png";//天数背景
static char IMG_GENERALS_SEVENACTIVITY_HALFPAY_BG[] = "images/activity/sevenActivity/image_sevenActivity_halfPay_bg.png";//半价背景
static char IMG_GENERALS_SEVENACTIVITY_LABEL[] = "images/activity/sevenActivity/image_sevenActivity_label.png";//开服狂欢七天乐
static char IMG_GENERALS_SEVENACTIVITY_PERSONAE[] = "images/activity/sevenActivity/image_sevenActivity_personae.png";//人物
//-----------------------------------------聊天-----------------------------------------//
static char IMG_CHAT_ADDFRIEND[]= "images/chat/img_chat_addFriend.png";//加好友
static char IMG_CHAT_SAY[]= "images/chat/img_chat_say.png";//按住说话
static char IMG_CHAT_MENU[]= "images/chat/img_chat_menu.png";//聊天框上的菜单
static char IMG_CHAT_LV[]= "images/chat/img_chat_lv.png";//等级
static char IMG_CHAT_REDDOT[] = "images/chat/img_chat_redDot.png";//红点
static char IMG_CHAT_SAYTRIANGLE[]= "images/chat/img_chat_sayTriangle.png";//聊天内容前面的三角
static char IMG_CHAT_SENDING[]= "images/chat/img_chat_sending.png";//正在发送
static char IMG_CHAT_FRIENDLISTLABEL[]= "images/chat/img_chat_friendListLabel.png";//好友列表
static char IMG_CHAT_FRIENDLISTLABEL2[]= "images/chat/img_chat_friendListLabel2.png";//好友列表2
static char IMG_CHAT_FRIENDAPPLYLABEL[]= "images/chat/img_chat_friendApplyLabel.png";//好友申请
static char IMG_CHAT_FRIENDAPPLYLABEL2[]= "images/chat/img_chat_friendApplyLabel2.png";//好友申请2
static char IMG_CHAT_KEYBOARD[]= "images/chat/img_chat_keyboard.png";//键盘
static char IMG_CHAT_CONTENTHEIGHT[]= "images/chat/img_chat_contentHeight.png";//聊天列表内容条
static char IMG_CHAT_SOCIALBTN[]= "images/chat/img_chat_socialBtn.png";//社交按钮
static char IMG_CHAT_INPUTBOX[]= "images/chat/img_chat_inputBox.png";//输入
static char IMG_CHAT_HEADBG[]= "images/chat/img_chat_headBg.png";//头像上背景
static char IMG_CHAT_FRIENDBG[]= "images/chat/img_chat_friendBg.png";//好友背景
static char IMG_CHAT_CONTENTSELECTED[]= "images/chat/img_chat_contentSelected.png";//选择三角
static char IMG_CHAT_MESSAGELISTLABEL[]= "images/chat/img_chat_messageListLabel.png";//消息列表
static char IMG_CHAT_MESSAGELISTLABEL2[]= "images/chat/img_chat_messageListLabel2.png";//消息列表2
static char IMG_CHAT_MESSAGENUMBG[]= "images/chat/img_chat_messageNumBg.png";//消息条数背景
static char IMG_CHAT_SELECTEDBG[]= "images/chat/img_chat_selectedBg.png";//消息列表选中背景
static char IMG_CHAT_TEMPHEAD[]= "images/chat/img_chat_tempHead.png";//临时头像
static char IMG_CHAT_LISTBG[]= "images/chat/img_chat_listBg.png";//消息列表框
static char IMG_CHAT_CELLBG[]= "images/chat/img_chat_cellBg.png";//列表背景
static char IMG_CHAT_FLOWERSIDE[]= "images/chat/img_chat_flowerSide.png";//花边
static char IMG_CHAT_SEARCH[]= "images/chat/img_chat_search.png";//搜索
static char IMG_CHAT_LINE[]= "images/chat/img_chat_line.png";//所搜线
static char IMG_CHAT_PLAYSOUND[] = "images/chat/img_chat_playSound.png";
static char IMG_CHAT_CHATBG[]= "images/chat/img_chat_chatBg.png";//聊天框背景
static char IMG_CHAT_SOUNDBTN[] = "images/chat/img_chat_soundBtn.png";//转声音按钮
static char IMG_CHAT_APPLY_BTN[] = "images/chat/img_chat_apply_btn.png";//好友申请
static char IMG_CHAT_LABEL_REJECT[] = "images/chat/img_chat_label_reject.png";//好友拒绝
static char IMG_CHAT_LABEL_AGREE[] = "images/chat/img_chat_label_agree.png";//好友同意
static char IMG_CHAT_ITEM_WHITE_BG[] = "images/chat/img_chat_item_white_bg.png";//白色背景
static char IMG_CHAT_ITEM_GREEN_BG[] = "images/chat/img_chat_item_green_bg.png";//绿色背景
static char IMG_CHAT_ITEM_WHITE_TRAN[] = "images/chat/img_chat_item_white_tran.png";//白色对话三角
static char IMG_CHAT_ITEM_GREEN_TRAN[] = "images/chat/img_chat_item_green_tran.png";//绿色对话三角
//

//---------------------------------------英雄装备--------------------------------------//
static char IMG_EQUIPMENT_HEROBGDOWN[] = "images/equipment/image_equipment_heroBgDown.png";
static char IMG_EQUIPMEN_HEROBGUP[] = "images/equipment/image_equipment_heroBgUp.png";
static char IMG_EQUIPMEN_EQUIPBG[] = "images/equipment/image_equipment_equipBg.png";
static char IMG_EQUIPMEN_EQUIP[] = "images/equipment/image_equipment_equip%s.png";
static char IMG_EQUIPMEN_HEROHEAD[] = "images/equipment/image_equipment_heroHead.png";
static char IMG_EQUIPMEN_PROGRESS[] = "images/equipment/image_equipment_progress.png";
static char IMG_EQUIPMEN_WORD[] = "images/equipment/image_equipment_word%s.png";
static char IMG_EQUIPMEN_DIRBTN[] = "images/equipment/image_equipment_dirBtn%s.png";
static char IMG_EQUIPMEN_BTN[] = "images/equipment/image_equipment_Btn.png";
static char IMG_EQUIPMEN_BTNCHOSE[] = "images/equipment/image_equipment_btnChose.png";
static char IMG_EQUIPMEN_BTNWORD[] = "images/equipment/image_equipment_btnWord%s.png";
static char IMG_EQUIPMEN_WEISPR[] = "images/equipment/image_equipment_weiSpr.png";

//----------------------------------------------------------------------------签到界面--------------------------------------------------------------//
static char IMG_SIGNIN_BG[] = "images/task/signin/image_signin_bg.png";
static char IMG_SIGNIN_POWERBG[] = "images/task/signin/image_signin_powerBg.png";
static char IMG_SIGNIN_POWERWORD[] = "images/task/signin/image_signin_poweWord.png";
static char IMG_SIGNIN_TIMEBG[] = "images/task/signin/image_signin_timeBg.png";

static char IMG_SIGNIN_COMBOBOX_BG[] = "images/task/signin/combobox/image_signin_box_bg.png";
static char IMG_SIGNIN_COMBOBOX_SELECTED[] = "images/task/signin/combobox/image_signin_box_selected.png";
//image_signin_box_selected.png
static char IMG_SIGNIN_COMBOBOX_LABEL[] = "images/task/signin/combobox/image_signin_box_label%s.png";
static char IMG_SIGNIN_COMBOBOX_MODULE[] = "images/task/signin/combobox/image_signin_box_module%s.png";
//每日签到
static char IMG_SIGNIN_EVERYDAY_BG[] = "images/task/signin/everydaySignin/image_signin_everyday_bg.png";
static char IMG_SIGNIN_EVERYDAY_CELL_BG[] = "images/task/signin/everydaySignin/image_signin_everyday_cell_bg.png";
static char IMG_SIGNIN_EVERYDAY_OTHER[] = "images/task/signin/everydaySignin/image_signin_everyday_other.png";
static char IMG_SIGNIN_EVERYDAY_VIPBG[] = "images/task/signin/everydaySignin/image_signin_everyday_vipBg.png";
//豪华签到
static char IMG_SIGNIN_LUXURY_PERSON[] = "images/task/signin/luxurySignin/image_signin_luxury_person.png";
static char IMG_SIGNIN_LUXURY_BTN[] = "images/task/signin/luxurySignin/image_signin_luxury_btn.png";
static char IMG_SIGNIN_LUXURY_LABEL2[] = "images/task/signin/luxurySignin/image_signin_luxury_label2.png";
static char IMG_SIGNIN_LUXURY_LABEL[] = "images/task/signin/luxurySignin/image_signin_luxury_label.png";
static char IMG_SIGNIN_LUXURY_PRIZE[] = "images/task/signin/luxurySignin/image_signin_luxury_prize.png";
static char IMG_SIGNIN_LUXURY_RECHARGE[] = "images/task/signin/luxurySignin/image_signin_luxury_recharge.png";
static char IMG_SIGNIN_LUXURY_TITLE[] = "images/task/signin/luxurySignin/image_signin_luxury_title.png";
//招财
static char IMG_SIGNIN_MONEYDRAW_BG[]="images/task/signin/moneyDraw/image_signin_moneyDraw_bg.jpg";
static char IMG_SIGNIN_MONEYDRAW_BOTTOM[]="images/task/signin/moneyDraw/image_signin_moneyDraw_bottom.jpg";
static char IMG_SIGNIN_MONEYDRAW_TOP[]="images/task/signin/moneyDraw/image_signin_moneyDraw_top.png";
static char IMG_SIGNIN_MONEYDRAW_DRAWWORD[]="images/task/signin/moneyDraw/image_signin_btnDrawWord.png";//祈福字
static char IMG_SIGNIN_MONEYDRAW_TITLEDRAW[]="images/task/signin/moneyDraw/image_signin_titleDraw.png";//祈福字

static char IMG_SIGNIN_MONEYDRAW_USE[]="images/task/signin/moneyDraw/image_signin_moneyDraw_use.png";
static char IMG_SIGNIN_MONEYDRAW_TODAYFINISH[]="images/task/signin/moneyDraw/image_signin_moneyDraw_todayFinish.png";
static char IMG_SIGNIN_MONEYDRAW_TOTAL[]="images/task/signin/moneyDraw/image_signin_moneyDraw_total.png";
static char IMG_SIGNIN_MONEYDRAW_REFRESH[]="images/task/signin/moneyDraw/image_signin_moneyDraw_refresh.png";
static char IMG_SIGNIN_MONEYDRAW_LABEL[]="images/task/signin/moneyDraw/image_signin_moneyDraw_label.png";
//福利
static char IMG_SIGNIN_BENEFIT_BG[]="images/task/signin/benefit/image_signin_benefit_bg.jpg";
static char IMG_SIGNIN_BENEFIT_DAY_BG[]="images/task/signin/benefit/image_signin_benefit_day_bg.png";
static char IMG_SIGNIN_BENEFIT_CELL_BG[]="images/task/signin/benefit/image_signin_benefit_day_cell_bg.png";
static char IMG_SIGNIN_BENEFIT_DAY_DRAWDOWN[]="images/task/signin/benefit/image_signin_benefit_day_drawDown.png";
static char IMG_SIGNIN_BENEFIT_DAY_OTHERLABEL[]="images/task/signin/benefit/image_signin_benefit_day_otherlabel.png";
static char IMG_SIGNIN_BENEFIT_DAY_OTHERLABEL2[]="images/task/signin/benefit/image_signin_benefit_day_otherLabel2.png";
static char IMG_SIGNIN_BENEFIT_PERSON[]="images/task/signin/benefit/image_signin_benefit_person.png";
static char IMG_SIGNIN_BENEFIT_VIP_BG1[]="images/task/signin/benefit/image_signin_benefit_vip_bg1.png";
static char IMG_SIGNIN_BENEFIT_VIP_BG2[]="images/task/signin/benefit/image_signin_benefit_vip_bg2.png";
static char IMG_SIGNIN_BENEFIT_WEEK_BG[]="images/task/signin/benefit/image_signin_benefit_week_bg.png";

static char IMG_SIGNIN_BENEFIT_WEEKSELL_BG[]="images/task/signin/benefit/image_signin_benefit_weeksellbg.png";//每周福利出售背景
static char IMG_SIGNIN_BENEFIT_WEEKPRICE_BG[]="images/task/signin/benefit/image_signin_benefit_week_pricebg.png";//每周福利价格背景
static char IMG_SIGNIN_BENEFIT_DAT_SPECIALFRAL[]="images/task/signin/benefit/image_signin_benefit_day_specialfral.png";//专属每日福利



//-----------------------------------集市界面-------------------------------------------//
static char IMG_MARKET_BOTTOMBG[] = "images/market/image_market_bottomBg.png";
static char IMG_MARKET_SHOPBG[] = "images/market/image_market_shopBg.png";
static char IMG_MARKET_JUXIANBG[] = "images/market/image_market_juxianBg.png";
static char IMG_MARKET_CARDBG[] = "images/market/image_market_cardBg.png";

//------------------------------------寻访...................................//
static char IMG_MARKET_WORDBTN[] = "images/market/image_market_word%s.png";
static char IMG_MARKET_WORDBTN_XUNFANG[] = "images/market/image_market_word5.png";//寻访
static char IMG_MARKET_WORDBTN_JUXIAN[] = "images/market/image_market_word6.png";//举贤
static char IMG_MARKET_WORDBTN_SHANGDIAN[] = "images/market/image_market_word4.png";//商店
static char IMG_MARKET_WORDBTN_PAIMAI[] = "images/market/image_market_word3.png";//拍卖
static char IMG_MARKET_WORDBTN_LIBAO[] = "images/market/image_market_word2.png";//礼包
static char IMG_MARKET_WORDBTN_HEISHI[] = "images/market/image_market_word1.png";//黑市
static char IMG_MARKET_MARKETFIND_BOTTOMSPR[] = "images/market/marketFind/image_market_bottomSpt.png";
static char IMG_MARKET_MARKETFIND_MAP[] = "images/market/marketFind/image_market_map1.png";
static char IMG_MARKET_MARKETFIND_UNBEGIN[] = "images/market/marketFind/image_market_unBegin.png";
static char IMG_MARKET_MARKETFIND_XUUNFANGWANCHENGSPR[] = "images/market/marketFind/image_market_xunfangwanchengSpr.png";
static char IMG_MARKET_MARKETFIND_XUNFANG[] = "images/market/marketFind/image_market_xunfang%s.png";
static char IMG_MARKET_MARKETFIND_INXUNFANG[] = "images/market/marketFind/image_market_inXunfang.png";
static char IMG_MARKET_MARKETFIND_KUOZHANSPR[] = "images/market/marketFind/image_market_kuozhanSpr.png";
static char IMG_MARKET_MARKETFIND_LASTTIMESPR[] = "images/market/marketFind/image_market_lasttimeSpr.png";
static char IMG_MARKET_MARKETFIND_XUNFANGWORD[] = "images/market/marketFind/image_market_xunfangWord.png";
static char IMG_MARKET_MARKETFIND_GRAYXUNFANGWORD[] = "images/market/marketFind/image_market_grayXunfangWord.png";
static char AVATAR_MARKET_KAIPAIGUANQIU[] = "images/market/marketFind/kaipaiguangqiu/choukapai.ExportJson";
static char AVATAR_MARKET_KAIPAIGUANXIAN[] = "images/market/marketFind/kapaigusngxian/kapaigusngxian.ExportJson";
static char AVATAR_MARKET_KAIPAIGUANQUAN[] = "images/market/marketFind/choukapaiguangquan/choukapaiguangquan.ExportJson";
static char IMG_MARKET_MARKETFIND_MILITARYBG[] = "images/market/marketFind/image_market_militarybg.png";
static char IMG_MARKET_MARKETFIND_MILITARYTIAO[] = "images/market/marketFind/image_market_militarytiao.png";
static char IMG_MARKET_MARKETFIND_MILITARYSLIDER[] = "images/market/marketFind/image_market_militarysload.png";
static char IMG_MARKET_MARKETFIND_FINDWORD[] = "images/market/marketFind/image_market_findword.png";

static char IMG_MARKET_MARKETFIND_MILITARYWORD[] = "images/market/marketFind/image_market_militaryword.png";
static char IMG_MARKET_MARKETFIND_MILITARYZHI[] = "images/market/marketFind/image_market_militaryzhi.png";
static char IMG_MARKET_MARKETFIND_SHIFOUJIASU[] = "images/market/marketFind/image_market_shifoujiasu.png";
static char IMG_MARKET_MARKETFIND_QUCHONGZHI[] = "images/market/marketFind/image_market_quchongzhi.png";
static char IMG_MARKET_MARKETFIND_EQUIPBG[] = "images/market/marketFind/findequip/image_market_bottomBg.png";
static char IMG_MARKET_MARKETFIND_EQUIPBUTTON[] = "images/market/marketFind/findequip/image_market_equipbutton.png";
static char IMG_MARKET_MARKETFIND_XUNFANGBUTTONBG[] = "images/market/marketFind/image_market_xunfangButtonBg.png";


//--------------------------------------举贤------------------------------------------//
static char IMG_MARKET_MARKETJUXIAN_JUXIANBG[] = "images/market/marketJuxian/image_market_juxianbg.png";
static char IMG_MARKET_MARKETJUXIAN_JUXIANWORD[] = "images/market/marketJuxian/image_market_juxianWord.png";



static char IMG_MARKET_MARKETJUXIAN_LIXIANXIASHI[] = "images/market/marketJuxian/image_market_lixianxiashi.png";
static char IMG_MARKET_MARKETJUXIAN_WEICAISHIJU[] = "images/market/marketJuxian/image_market_weicaishiju.png";
static char IMG_MARKET_MARKETJUXIAN_QIUXIANRUOKE[] = "images/market/marketJuxian/image_market_qiexianruoke.png";
static char IMG_MARKET_MARKETJUXIAN_JUXIANBIGBG[] = "images/market/marketJuxian/image_market_juxianbigbg.png";
static char IMG_MARKET_MARKETJUXIAN_BOTTOMBG[] = "images/market/marketJuxian/image_market_bottomBg.png";//底座
static char IMG_MARKET_MARKETJUXIAN_CARD[] = "images/market/marketJuxian/image_market_card%s.png";//低中高级卡牌
static char IMG_MARKET_MARKETJUXIAN_CARDCLOR[] = "images/market/marketJuxian/image_market_cardclor%s.png";//低中高级卡牌
static char AVATAR_MARKET_CARDTURN[] = "images/market/marketJuxian/kapai360/kapai360.ExportJson";
static char AVATAR_MARKET_CARDXUANZHONG[] = "images/market/marketJuxian/kapaixuanzhong/kapaixuanzhong.ExportJson";
static char IMG_MARKET_MARKEFIND_FINDBG[] = "images/market/image_market_findBg.jpg";//beijing




//--------------------------------------商店------------------------------------------//
static char IMG_MARKET_MARKETSHOP_SHOPWORD[] = "images/market/marketShop/image_market_shop_shangdianWord.png";
static char IMG_MARKET_MARKETSHOP_ADD[] = "images/market/marketShop/image_market_shop_add.png";
static char IMG_MARKET_MARKETSHOP_ADDTEN[] = "images/market/marketShop/image_market_shop_addTen.png";
static char IMG_MARKET_MARKETSHOP_ALLPRICE[] = "images/market/marketShop/image_market_shop_allPrice.png";

static char IMG_MARKET_MARKETSHOP_BUYTIME[] = "images/market/marketShop/image_market_shop_buyTime.png";
static char IMG_MARKET_MARKETSHOP_LITTLEBG[] = "images/market/marketShop/image_market_shop_littleBg.png";
static char IMG_MARKET_MARKETSHOP_MIN[] = "images/market/marketShop/image_market_shop_min.png";
static char IMG_MARKET_MARKETSHOP_MINTEN[] = "images/market/marketShop/image_market_shop_minTen.png";
static char IMG_MARKET_MARKETSHOP_NOWHAVE[] = "images/market/marketShop/image_market_shop_nowHave.png";
static char IMG_MARKET_MARKETSHOP_PRICEBG[] = "images/market/marketShop/image_market_shop_priceBg.png";
static char IMG_MARKET_MARKETSHOP_GTAYSHOP[] = "images/market/marketShop/image_market_shop_shangdianWordGray.png";
static char IMG_MARKET_MARKETSHOP_DAOJUBG[] = "images/market/marketShop/image_market_shop_daojubg.png";
static char IMG_MARKET_MARKETSHOP_DAOJUNAME[] = "images/market/marketShop/image_market_shop_daoju.png";
static char IMG_MARKET_MARKETSHOP_REMOVELINE[] = "images/market/marketShop/image_market_shop_removeLine.png";//删除线
static char AVATAR_MARKET_GOLDFLY[] = "images/market/marketShop/shangdianjingbi/shangdianjingbi.ExportJson";


//--------------------------------------拍卖------------------------------------------//

static char IMG_MARKET_AUCTION_PAIMAIWORD[] = "images/market/marketAuction/image_market_aucton_paimaiword.png";//拍卖字体
static char IMG_MARKET_AUCTION_PAIMAISUO[] = "images/market/marketAuction/image_market_aucton_paimaisuo.png";//拍卖所
static char IMG_MARKET_AUCTION_QUCHUSHOU[] = "images/market/marketAuction/image_market_aucton_quchushou.png";//去出售
static char IMG_MARKET_AUCTION_SHANGJIAZHONG[] = "images/market/marketAuction/image_market_aucton_shangjiazhong.png";//上架中
static char IMG_MARKET_AUCTION_JIAGE[] = "images/market/marketAuction/image_market_aucton_jiage.png";//价格
static char IMG_MARKET_AUCTION_SHENGYU[] = "images/market/marketAuction/image_market_aucton_shengyu.png";//剩余
static char IMG_MARKET_AUCTION_RIGHTBG[] = "images/market/marketAuction/image_market_aucton_rightBg.png";//右侧背景
static char IMG_MARKET_AUCTION_UNCHOSE[] = "images/market/marketAuction/image_market_aucton_unchose.png";//未选中
static char IMG_MARKET_AUCTION_SELLPEOPLE[] = "images/market/marketAuction/image_market_aucton_sellpeople.png";//出售人
static char IMG_MARKET_AUCTION_SERCH[] = "images/market/marketAuction/image_market_aucton_serch.png";//搜索
static char IMG_MARKET_AUCTION_SERCHBG[] = "images/market/marketAuction/image_market_aucton_serchBg.png";//搜索背景
static char IMG_MARKET_AUCTION_HEADBG[] = "images/market/marketAuction/image_market_headBg.png";//头像背景
static char IMG_MARKET_AUCTION_ADD[] = "images/market/marketAuction/image_market_aucton_add.png";//加按钮（大）
static char IMG_MARKET_AUCTION_MIN[] = "images/market/marketAuction/image_market_aucton_min.png";//减按钮（大）
static char IMG_MARKET_AUCTION_XIAJIAWORD[] = "images/market/marketAuction/image_market_aucton_xiajiaword.png";//下架字体
static char IMG_MARKET_AUCTION_BG[] = "images/market/marketAuction/image_market_aucton_bg.png";//
//static char IMG_MARKET_AUCTION_CELLBG[] = "images/market/marketAuction/image_market_aucton_cellbg.png";//
//static char IMG_MARKET_AUCTION_CELLBGBOX[] = "images/market/marketAuction/image_market_aucton_bgbox.png";//


//---------------------------------------------------任务界面--------------------------------------------------------//
static char IMG_TASK_RIGHTBTNBG[] = "images/task/image_task_rightBtnBg.png";
static char IMG_TASK_RIGHTBTN[] = "images/task/image_task_rightBtn%s.png";
static char IMG_TASK_GRAYBG[] = "images/task/image_task_graybg.png";
static char IMG_TASK_ITEMBG[] = "images/task/image_task_itemBg.png";//任务背景条
static char IMG_TASK_TASTPRICE[] = "images/task/image_task_tastprice.png";//任务奖励
//------------------------------------普通------------------------------------//


static char IMG_TASK_PUTONG_PTRWWORD[] = "images/task/putong/image_task_putong_ptrwWord.png";
static char IMG_TASK_PUTONG_PTRWGRAY[] = "images/task/putong/image_task_putong_ptrwGray.png";
static char IMG_TASK_PUTONG_BALL[] = "images/task/putong/image_task_putong_ball.png";

//------------------------------------日常------------------------------------//
static char IMG_TASK_RICAHNG_JIFEN[] = "images/task/richang/image_task_ricahng_jifen.png";
static char IMG_TASK_RICAHNG_LINE[] = "images/task/richang/image_task_ricahng_line.png";
static char IMG_TASK_RICAHNG_UPPROGRESS[] = "images/task/richang/image_task_ricahng_uppro.png";
static char IMG_TASK_RICAHNG_DOWNPROGRESS[] = "images/task/richang/image_task_ricahng_downpro.png";
static char IMG_TASK_RICAHNG_RESET[] = "images/task/richang/image_task_ricahng_reset.png";
static char IMG_TASK_RICAHNG_JIFENBG[] = "images/task/richang/image_task_ricahng_jifenBg.png";
//static char IMG_TASK_RICAHNG_BOX[] = "images/task/richang/image_task_ricahng_box.png";
static char IMG_TASK_RICAHNG_RCRWWORD[] = "images/task/richang/image_task_ricahng_rcrwWord.png";
static char IMG_TASK_RICAHNG_RCRWWORDGRAY[] = "images/task/richang/image_task_ricahng_rcrwWordGray.png";



//------------------------------------vip------------------------------------//
static char IMG_VIP_RECHARGEBG[] = "images/vip/image_vip_rechargebg.jpg";//剩余时间
static char IMG_VIP_HUMANPIC[] = "images/vip/image_vip_humanpic.png";//黑市字体
static char IMG_VIP_TEQUANBG[] = "images/vip/image_vip_tequanbg.png";//特权背景
static char IMG_VIP_BTN[] = "images/vip/image_vip_btn%s.png";//选中
static char IMG_VIP_BTNWORD[] = "images/vip/image_vip_btnWord%s.png";//选中
//------------------------------------vip充值------------------------------------//
static char IMG_VIP_RECHARGE_BUYTITLE[] = "images/vip/recharge/image_vip_recharge_buytitle.png";//已购买
static char IMG_VIP_RECHARGE_ABLEGET[] = "images/vip/recharge/image_vip_recharge_ableget.png";//可领取
static char IMG_VIP_RECHARGE_TODAY_GETTED[] = "images/vip/recharge/image_vip_recharge_todayGetted.png";//已领取


static char IMG_VIP_RECHARGE_YUEKABG[] = "images/vip/recharge/image_vip_recharge_yuekabg%s.png";//月卡背景
static char IMG_VIP_RECHARGE_YUEKABGMONEY[] = "images/vip/recharge/image_vip_recharge_yuekabgmoney%s.png";//月卡背景
static char IMG_VIP_RECHARGE_YUEKAWORD[] = "images/vip/recharge/image_vip_recharge_yuekabgword%s.png";//月卡字体
static char IMG_VIP_RECHARGE_FIRSTRECHARGE[] = "images/vip/recharge/image_vip_recharge_firstrecharge.png";//首充字体
static char IMG_VIP_RECHARGE_ALLGOLD[] = "images/vip/recharge/image_vip_recharge_allgold.png";//元宝堆


static char IMG_VIP_RECHARGE_FIRSTRECHARGEWORD[] = "images/vip/recharge/image_vip_recharge_firstrechargeword.png";//首充额外赠
static char IMG_VIP_RECHARGE_GOLD[] = "images/vip/recharge/image_vip_recharge_gold.png";//元宝
static char IMG_VIP_RECHARGE_JIDEMEIRILINGQUWORD[] = "images/vip/recharge/image_vip_recharge_jidemeiriword.png";//记得每日领取字体
static char IMG_VIP_RECHARGE_PUTONGRECHARGEBG[] = "images/vip/recharge/image_vip_recharge_putongrechargebg.png";//普通充值背景
static char IMG_VIP_RECHARGE_SPERECHARGEBG[] = "images/vip/recharge/image_vip_recharge_sperechagebg.png";//特殊充值背景
static char IMG_VIP_RECHARGE_TEQUANBEN[] = "images/vip/recharge/image_vip_recharge_tequanbtn.png";//特权按钮
static char IMG_VIP_RECHARGE_VIPBG[] = "images/vip/recharge/image_vip_recharge_vipdengji.png";//VIP背景
static char IMG_VIP_RECHARGE_VIPPROGRESS[] = "images/vip/recharge/image_vip_recharge_vipprogress.png";//VIP进度条
static char IMG_VIP_RECHARGE_VIPDOWNPROGRESS[] = "images/vip/recharge/image_vip_recharge_downvipprogress.png";//VIP进度条背景
static char IMG_VIP_RECHARGE_VIPLEVEL[] = "images/vip/recharge/image_vip_recharge_viplevel.png";//VIP等级提示
static char IMG_VIP_RECHARGE_SAMEUSER[] = "images/vip/recharge/image_vip_recharge_sameuser.png";//同时生效
static char IMG_VIP_RECHARGE_OTHERBTN[] = "images/vip/recharge/image_vip_recharge_otherbtn.png";//其他充值
static char IMG_VIP_RECHARGE_OTHERWORD[] = "images/vip/recharge/image_vip_recharge_otherrecWord.png";//其他充值zi
static char IMG_VIP_RECHARGE_NOWHAVE[] = "images/vip/recharge/image_vip_recharge_nowhave.png";//当前拥有
static char IMG_VIP_RECHARGE_RECCOUNT[] = "images/vip/recharge/image_vip_recharge_recCount.png";//充值数量
static char IMG_VIP_RECHARGE_RECBTN[] = "images/vip/recharge/image_vip_recharge_recbtn.png";//按钮
static char IMG_VIP_RECHARGE_ADDRECFIVTY[] = "images/vip/recharge/image_vip_recharge_addrecbtnfivty.png";//加50
static char IMG_VIP_RECHARGE_MINRECFIVTY[] = "images/vip/recharge/image_vip_recharge_minrecbtnfivty.png";//-50
static char IMG_VIP_RECHARGE_MINRECBTNTEN[] = "images/vip/recharge/image_vip_recharge_minrecbtnten.png";//-10
static char IMG_VIP_RECHARGE_ADDRECBTNTEN[] = "images/vip/recharge/image_vip_recharge_addrecbtnten.png";//+10

//------------------------------------vip黑市------------------------------------//
static char IMG_VIP_BLACKSHOP_RELEATETIME[] = "images/vip/blackshop/image_vip_blackshop_retaintime.png";//剩余时间
static char IMG_VIP_BLACKSHOP_SHUAXIN[] = "images/vip/blackshop/image_vip_blackshop_shuaxinword.png";//刷新
//------------------------------------vip礼包------------------------------------//
static char IMG_VIP_LIBAO_LIBAOBG[] = "images/vip/libao/image_vip_libao_libaobg.png";//背景
static char IMG_VIP_LIBAO_CELLLIBAOBG[] = "images/vip/libao/image_vip_libao_cellBg.png";//单个背景
static char IMG_VIP_LIBAO_GIFTHEAD[] = "images/vip/libao/image_vip_libao_gifthead.png";//礼包头像
static char IMG_VIP_LIBAO_LIBAOWORD[] = "images/vip/libao/image_vip_libao_libaoWord.png";//超值礼包
static char IMG_VIP_LIBAO_LINE[] = "images/vip/libao/image_vip_libao_line.png";//XIAN
static char IMG_VIP_LIBAO_YUANJIA[] = "images/vip/libao/image_vip_libao_yuanjia.png";//原价
static char IMG_VIP_LIBAO_ZHEKOUJIAWORD[] = "images/vip/libao/image_vip_libao_zhekoujiaWord.png";//折扣价


//------------------------------------------设置界面--------------------------------------------//
static char IMG_SETUP_NANEBG[] = "images/setup/image_setup_namebg.png";//名字背景
static char IMG_SETUP_SETUPWORD[] = "images/setup/image_setup_setsupword.png";//设置字
static char IMG_SETUP_MUSIC[] = "images/setup/image_setup_music.png";//音乐
static char IMG_SETUP_YINXIAO[] = "images/setup/image_setup_yinxiao.png";//音效
static char IMG_SETUP_SWITCHBG[] = "images/setup/image_setup_switchbg.png";//开关背景
static char IMG_SETUP_SWITCHBTN[] = "images/setup/image_setup_switchbtn.png";//开关按钮
static char IMG_SETUP_SMUSICNTNBG[] = "images/setup/image_setup_musicbtnbg.png";//开关按钮
static char IMG_SETUP_ACATIVETIONCODE[] = "images/setup/image_setup_activationCode.png";//激活码
static char IMG_SETUP_PROCESSGROMBG[] = "images/setup/image_setup_processgrombg.png";//经验条背景
static char IMG_SETUP_PROCESSGROM[] = "images/setup/image_setup_processgrom.png";//经验条
static char IMG_SETUP_PROCESSGROMWORD[] = "images/setup/image_setup_processgrWord.png";//经验条zi




//------------------------------------------ 邮件界面--------------------------------------------//
static char IMG_MAIL_LAYERBG[] = "images/mail/image_mail_layerbg.png";//界面背景
static char IMG_MAIL_CELLBG[] = "images/mail/image_mail_cellbg.png";//cell背景
static char IMG_MAIL_GIFTBTN[] = "images/mail/image_mail_giftbtn.png";//按钮
static char IMG_MAIL_LINE[] = "images/mail/image_mail_line.png";//线
static char IMG_MAIL_MAILBG[] = "images/mail/image_mail_mailbg.png";//内容背景
static char IMG_MAIL_MAILWORD[] = "images/mail/image_mail_mailword.png";//邮件字
static char IMG_MAIL_RECEIVEWORD[] = "images/mail/image_mail_reciiveword.png";//一键领取
static char IMG_MAIL_TOPLIBLE[] = "images/mail/image_mail_toplible.png";//邮件头


//------------------------------------------扫荡界面--------------------------------------------//
static char IMG_SWEEP_PIC[] = "images/sweep/image_sweep_pic.png";
static char IMG_SWEEP_PICJY[] = "images/sweep/image_sweep_picJy.png";
static char IMG_SWEEP_PICPT[] = "images/sweep/image_sweep_picPt.png";

static char IMG_SWEEP_SAODANGWORD[] = "images/sweep/image_sweep_saodangWord.png";

static char IMG_SWEEP_STAR[] = "images/sweep/image_sweep_star.png";


static char IMG_SWEEP_TOPSPR[] = "images/sweep/image_sweep_topSpr.png";
static char IMG_SWEEP_NAMEBG[] = "images/sweep/image_sweep_nameBg.png";

static char IMG_SWEEP_BOXBG[] = "images/sweep/image_sweep_bg.png";//框架

static char IMG_SWEEP_BUTTOMONE[] = "images/sweep/image_sweep_bottomone.png";//第一幕
static char IMG_SWEEP_BUTTOMTWO[] = "images/sweep/image_sweep_bottomtwo.png";//第二幕
static char IMG_SWEEP_BUTTOMTHREE[] = "images/sweep/image_sweep_bottomthree.png";//第三幕
static char IMG_SWEEP_BUTTOMSAODANG[] = "images/sweep/image_sweep_buttonsaodang.png";//扫荡
static char IMG_SWEEP_BUTTOMSAODANGZHONG[] = "images/sweep/image_sweep_buttonsaodangonezhong.png";//扫荡选中
static char IMG_SWEEP_BUTTOMSAODANGONE[] = "images/sweep/image_sweep_buttonsaodangone.png";//扫荡一次
static char IMG_SWEEP_BUTTOMSAODANGFIVE[] = "images/sweep/image_sweep_buttonsaodangonefive.png";//扫荡五次

static char IMG_SWEEP_BUTTOMSAODANGUNCHOSE[] = "images/sweep/image_sweep_buttonsaodangunchose.png";//未选中
static char IMG_SWEEP_STARBG[] = "images/sweep/image_sweep_starbg.png";//宝箱背景
static char IMG_SWEEP_BOXSPR[] = "images/sweep/image_sweep_boxspr%s.png";//框架背景


////////////////////////战斗信息界面、、//////////////////////////////////////////////////////////////////////
static char IMG_STAGEBATTLEINFO_BG[] = "images/stageBattleInfo/image_stageBattleInfo_Bg.png";
static char IMG_STAGEBATTLEINFO_ENGERGAME[] = "images/stageBattleInfo/image_stageBattleInfo_enterGame.png";
static char IMG_STAGEBATTLEINFO_ONE[] = "images/stageBattleInfo/image_stageBattleInfo_one.png";
static char IMG_STAGEBATTLEINFO_TEN[] = "images/stageBattleInfo/image_stageBattleInfo_ten.png";
static char IMG_STAGEBATTLEINFO_BOXBG[] = "images/stageBattleInfo/image_stageBattleInfo_boxBg.png";
static char IMG_STAGEBATTLEINFO_SELECTED[] = "images/stageBattleInfo/image_stageBattleInfo_selected.png";

static char IMG_SWEEP_BOTTOMSPR[] = "images/stageBattleInfo/image_sweep_bottomSpr.png";
static char IMG_SWEEP_BOTTOMFIGHT[] = "images/stageBattleInfo/image_sweep_bottomfoght.png";//进入战斗
static char IMG_SWEEP_BUTTOMSAODANGCHOSE[] = "images/stageBattleInfo/image_sweep_buttonsaodangchose.png";//选中

//--------------------------------------------登陆界面login-------------------------------------------------------------------
static char IMG_LOGIN_BG[] = "images/login/image_login_bg.png";
static char IMG_LOGIN_BG_EFFECT[] = "images/login/dengluliemian/dengluliemian.ExportJson";
static char IMG_LOGIN_ENTERBG[] = "images/login/image_serverlist_enterBg.png";//进入游戏背景
static char IMG_LOGIN_ENTERWORD[] = "images/login/image_loading_enterWord.png";//


static char IMG_LOADING_INPUTBG[] = "images/login/image_loading_inputBg.png";//输入背景框
static char IMG_LOADING_TOURSISTBTN[] = "images/login/image_loading_touristBtn.png";//游客登陆
static char IMG_LOADING_LOGINBTN[] = "images/login/image_loading_loginBtn.png";//登陆


//服务器列表
static char IMG_SERVERLIST_LASTBTN[] = "images/login/serverList/image_serverlist_lastLogin.png";
static char IMG_SERVERLIST_LASTBTN1[] = "images/login/serverList/image_serverlist_lastLogin1.png";
static char IMG_SERVERLIST_BG[] = "images/login/serverList/image_serverlist_bg.png";
static char IMG_SERVERLIST_TITLE[] = "images/login/serverList/image_serverlist_title.png";
static char IMG_SERVERALLLIST_TITLE[] = "images/login/serverList/image_serveralllist_title.png";//全部服务器

static char IMG_SERVERLIST_BUSY[] = "images/login/serverList/image_serverlist_busy.png";
static char IMG_SERVERLIST_MAINTAIN[] = "images/login/serverList/image_serverlist_mainTain.png";//维护
static char IMG_SERVERLIST_SMOOTH[] = "images/login/serverList/image_serverlist_smooth.png";//顺畅

static char IMG_SERVERLIST_ITEMBG1[] = "images/login/serverList/image_serverlist_itemBg1.png";
static char IMG_SERVERLIST_AREAITEM[] = "images/login/serverList/image_serverList_areaItem.png";
static char IMG_SERVERLIST_AREAITEM1[] = "images/login/serverList/image_serverList_areaItem1.png";

//static char IMG_SERVERLIST_CONFIRM[] = "images/login/serverList/image_serverlist_confirm.png";
//static char IMG_SERVERLIST_RELGOIN[] = "images/login/serverList/image_serverlist_relogin.png";


//---------------------------------------------三国无双------------------------------------------------------------------------------
static char IMG_MUSOU_LEFTTIMEWORD[] = "images/musouLayer/image_musou_leftTimeWord.png";
static char IMG_MUSOU_LEFTTIMEBG[] = "images/musouLayer/image_musou_leftTimeBg.png";
static char IMG_MUSOU_STAGEBG[] = "images/musouLayer/musouBg/%s.png";
static char IMG_MUSOU_STAGE_ELEMENT[] = "images/musouLayer/musouEle/%s.png";
static char IMG_MUSOU_GUAN[] = "images/musouLayer/musouBg/image_musouBg_guan.png";
static char IMG_MUSOU_KAI[] = "images/musouLayer/musouBg/image_musouBg_kai.png";
static char IMG_MUSOU_SEE[] = "images/musouLayer/musouBg/image_musouBg_see.png";



static char IMG_MUSOUBATTLE_LEFTTIMEBG[] = "images/musouLayer/musouBattle/image_musoubattle_leftTimeBg.png";//剩余时间
static char IMG_MUSOUBATTLE_LEVEL[] = "images/musouLayer/musouBattle/image_musouBattle_level%s.png";//无双战斗等次
static char IMG_MUSOUBATTLE_CENTERBG[] = "images/musouLayer/musouBattle/image_musouBattle_itemCenter.png";//中部层
static char IMG_MUSOUBATTLE_FRONT[] = "images/musouLayer/musouBattle/image_musouBattle_itemFront%s.png";//小图框


static char IMG_MUSOUBATTLE_BG[] = "images/musouLayer/musouBattle/image_musouBattle_bg.png";//背景
static char IMG_MUSOUBATTLE_UNLOCKLEVEL[] = "images/musouLayer/musouBattle/image_musouBattle_unLockLevel.png";//解锁背景
static char IMG_MUSOUBATTLE_LOCK[] = "images/musouLayer/musouBattle/image_musouBattle_lock.png";//锁

//---------------------------------------------首充------------------------------------------------------------------------------
static char ING_FIRSTRECHARGE_BG[] = "images/firstRecharge/image_firstRecharge_Bg.png"; //首充背景
static char ING_FIRSTRECHARGE_RECHARGE[] = "images/firstRecharge/image_firstRecharge_recharge.png"; //前往充值
static char ING_FIRSTRECHARGE_LINGQU[] = "images/firstRecharge/image_firstRecharge_lingqu.png"; //前往充值
//----------------------------------------------限时抽卡---------------------------------------------
static char IMG_LIMITCARD_BG[] = "images/limitCard/image_limit_bg.png";//背景
static char IMG_LIMITCARD_DENMAGEFIVE[] = "images/limitCard/image_limit_demagefive.png";//五倍伤害
static char IMG_LIMITCARD_ONETIME[] = "images/limitCard/image_limit_onetime.png";//抽卡一次
static char IMG_LIMITCARD_TENTIME[] = "images/limitCard/image_limit_tentime.png";//抽卡十次
static char IMG_LIMITCARD_SKILLSEE[] = "images/limitCard/image_limit_skillSee.png";//技能查看
static char IMG_LIMITCARD_SKILLBG[] = "images/limitCard/image_limit_skillbg.png";//技能背景
static char IMG_LIMITCARD_SKILLONEBG[] = "images/limitCard/image_limit_skillonebg.png";//技能内容背景
static char IMG_LIMITCARD_SKILLONETITLE[] = "images/limitCard/image_limit_skilltitle.png";//技能详情字
static char IMG_LIMITCARD_SKILLONETITLEBG[] = "images/limitCard/image_limit_skilltitlebg.png";//技能详情背景

//----------------------------------------------名将传排名---------------------------------------------
static char IMG_RANK_CELLBG[] = "images/rank/image_rank_cellbg.png";//列表底层
static char IMG_RANK_ALLRANKWORD[] = "images/rank/image_rank_allrankword.png";//综合排名
static char IMG_RANK_ALLRANKWORDCHOSE[] = "images/rank/image_rank_allrankwordchose.png";//综合排名选中
static char IMG_RANK_AWARDWORD[] = "images/rank/image_rank_awardword.png";//奖励列表
static char IMG_RANK_DAYRANK[] = "images/rank/image_rank_dayrankword.png";//每日排名
static char IMG_RANK_DAYRANKCHOSE[] = "images/rank/image_rank_dayrankwordchose.png";//每日排名选中
static char IMG_RANK_FIRST[] = "images/rank/image_rank_first.png";//第一名
static char IMG_RANK_SECOND[] = "images/rank/image_rank_second.png";//第二名
static char IMG_RANK_THIRD[] = "images/rank/image_rank_third.png";//第三名
static char IMG_RANK_PERSON[] = "images/rank/image_rank_person.png";//个人详情
static char IMG_RANK_RANKPRICE[] = "images/rank/image_rank_rankprice.png";//排名奖励
static char IMG_RANK_NOONEPRIVE[] = "images/rank/image_rank_nooneprice.png";//第一名奖励
static char IMG_RANK_FRIENDWORD[] = "images/rank/image_rank_friendword.png";//加好友

//--------------------------------------------------名将传活动----------------------------------------------------
static char IMG_FAMOUSE_ACTIVE_BOSSBG[] = "images/famouseGeneral/active/image_famouse_active_bossBg.png";//boss底层
static char IMG_FAMOUSE_ACTIVE_SCOREBG[] = "images/famouseGeneral/active/image_famouse_active_scoreBg.png";//分数底层
static char IMG_FAMOUSE_HEROITEMBG[] = "images/famouseGeneral/image_famouse_heroItemBg.png";
static char IMG_FAMOUSE_DISCOVERMAN[] = "images/famouseGeneral/image_famouse_discoverMan.png";//发现者
static char IMG_FAMOUSE_SUPPORT[] = "images/famouseGeneral/image_famouse_support.png";//支援者
static char IMG_FAMOUSE_SUPPORTMAN[] = "images/famouseGeneral/image_famouse_supportMan.png";//支援人数
static char IMG_FAMOUSE_HURTCOUNT[] = "images/famouseGeneral/image_famouse_hurtCount.png";//造成伤害
static char IMG_FAMOUSE_DELAYTIME[] = "images/famouseGeneral/image_famouse_delayTime.png";//延时时间
static char IMG_FAMOUSE_BLOODREDPRO[] = "images/famouseGeneral/image_famouse_bloodred.png";//血条红
static char IMG_FAMOUSE_BLOODGREENPRO[] = "images/famouseGeneral/image_famouse_bloodgreen.png";//血条绿
static char IMG_FAMOUSE_BLOODYELLOWPRO[] = "images/famouseGeneral/image_famouse_bloodyellow.png";//血条黄
static char IMG_FAMOUSE_CHALLENGECOUNT[] = "images/famouseGeneral/image_famouse_challengeCount.png";//挑战次数
static char IMG_FAMOUSE_ACTIVETIME[] = "images/famouseGeneral/image_famouse_activeTime.png";//活动时间
static char IMG_FAMOUSE_EASECAPE_TIME[] = "images/famouseGeneral/image_famouse_easecapeTime.png";//逃跑剩余时间
static char IMG_FAMOUSE_ATTACKLOSE[] = "images/famouseGeneral/image_famouse_attackLost.png";//击败了
static char IMG_FAMOUSE_WEI[] = "images/famouseGeneral/image_famouse_wei.png";
static char IMG_FAMOUSE_BOSSLEVEL[] = "images/famouseGeneral/image_famouse_bossLevel.png";//boss等级
static char IMG_FAOUSE_FRIENDWORD[] = "images/famouseGeneral/image_famouse_friendWord.png";
//名将传详情
static char IMG_FAMOUSE_DETAILS_BOSSBG[] = "images/famouseGeneral/details/image_famouse_details_bossBg.png";//详情boss底层
static char IMG_FAMOUSE_DETAILS_SCOREBG[] = "images/famouseGeneral/details/image_famouse_details_scoreBg.png";//分数
static char IMG_FAMOUSE_DETAILS_ITEMBG[] = "images/famouseGeneral/details/image_famouse_detailsItembg.png";
static char IMG_FAMOUSE_DETAILS_SUC[] = "images/famouseGeneral/details/image_famouse_details_suc.png";//
static char IMG_FAMOUSE_DETAILS_FAILS[] = "images/famouseGeneral/details/image_famouse_details_fails.png";//
static char IMG_FAMOUSE_DETAILS_TOP[] = "images/famouseGeneral/details/image_famouse_details_top.png";

//名将来袭
static char IMG_FAMOUSE_COMEBG[] = "images/famouseGeneral/famouseCome/image_famouse_comeBg.png";//场景背景
static char IMG_FAMOUSE_INFOBG[] = "images/famouseGeneral/famouseCome/image_famouse_infoBg.png";//信息背景
static char IMG_FAMOUSE_COME_TITLE[] = "images/famouseGeneral/famouseCome/image_famouse_cometitle.png";//名将来袭
static char IMG_FAMOUSE_COME_BLOOD[] = "images/famouseGeneral/famouseCome/image_famousecome_blood.png";//血条
static char IMG_FAMOUSE_COME_BLOODBG[] = "images/famouseGeneral/famouseCome/image_famousecome_bloodBg.png";//血条背景
//名将结算
static char IMG_FAMOUSE_SETTLE_BG[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_bg.png";//结算背景
static char IMG_FAMOUSE_SETTLE_HIT[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_hit.png";//击杀
static char IMG_FAMOUSE_SETTLE_VS[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_vs.png";//
static char IMG_FAMOUSE_SETTLE_LEFTTIME[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_leftTime.png";//逃跑剩余时间
static char IMG_FAMOUSE_SETTLE_WINTITLE[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_winTitle.png";//胜利
static char IMG_FAMOUSE_SETTLE_LOSETITLE[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_loseTitle.png";//失败
static char IMG_FAMOUSE_SETTLE_VIEW[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_view.png";//查看
static char IMG_FAMOUSE_SETTLE_END[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_end.png";//结束
static char IMG_FAMOUSE_SETTLE_SUPPORT[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_support.png";//支援
static char IMG_FAMOUSE_SETTLE_AGAIN[] = "images/famouseGeneral/famouseSettle/image_famouse_settle_again.png";//再战

//人物升级
//

static char IMG_LEVELUP_ITEMS[] = "images/levelUp/image_levelUP_items.png";

//竞技场
static char IMG_ARENA_CURORDER[] = "images/arena/img_arenaList_curOrder.png";//当前排名
static char IMG_ARENA_BGE[] = "images/arena/img_arenaList_bge.png";//战斗力
static char IMG_ARENA_RECORDETITLE[] = "images/arena/img_arenaList_recoderTitle.png";//战斗记录
static char IMG_ARENA_RECORDETITLE1[] = "images/arena/img_arenaList_recoderTitle1.png";//对战记录
static char IMG_ARENA_INSTRUCTIONTITLE[] = "images/arena/img_arena_instructionTitle.png";//说明
static char IMG_ARENA_HONOR[] = "images/arena/img_arena_honor.png";//荣誉
static char IMG_ARENA_NOWHONOR[] = "images/arena/img_arena_nowHonor.png";//当前荣誉
static char IMG_ARENA_BOTTOM_INSTRUCTION[] = "images/arena/img_arena_bottomInstruction.png";//底部说明
static char IMG_ARENA_COUNTVALUE[] = "images/arena/img_arena_countValue.png";//竞技次数
static char IMG_ARENA_NOWORDERPRIZE[] = "images/arena/img_arena_nowOrderPrize.png";//当前排名奖励
static char IMG_ARENA_TOP_PRIZE[] = "images/arena/img_arena_top_prize.png";//每日21点发放
static char IMG_ARENA_EXCHAGETITLE[] = "images/arena/img_arena_exchangeTitle.png";//兑换
static char IMG_ARENA_FIGHTTIME[] = "images/arena/img_arena_fighttime.png";//挑战倒计时

static char IMG_ARENA_RACETITLE[] = "images/arena/img_arena_raceTitle.png";//竞技
static char IMG_ARENA_TEANTITLE[] = "images/arena/img_arena_teamTitle.png";//阵容
static char IMG_ARENA_ORDERTITLE[] = "images/arena/img_arena_orderTitle.png";//排行标题

static char IMG_ARENA_HISTORYBEST_CONTENT[] = "images/arena/historyBest/image_arena_historyBest_content.png";//历史最高内容
static char IMG_ARENA_HISTORYBEST_WORD[] = "images/arena/historyBest/image_arena_historyBest_word.png";//历史最高
static char IMG_ARENA_WINBG[] = "images/arena/historyBest/image_arena_winBg.png";//胜利背景

static char IMG_ARENALIST_CHANGETITLE[] = "images/arena/arenaList/img_arenaList_changeTitle.png";//换一组
static char IMG_ARENALIST_TIAOZHAN[] = "images/arena/arenaList/img_arenaList_tiaozhan.png";//挑战
static char IMG_ARENALIST_COIN[] = "images/arena/arenaList/img_arenaList_coin.png";//铜钱
static char IMG_ARENATEAM_ITEMBG[] = "images/arena/team/img_arena_teamItemBg.png";
static char IMG_ARENATEAM_EDIT[] = "images/arena/team/img_arena_teamEdit.png";//编辑
static char IMG_ARENATEAM_SELECTED[] = "images/arena/team/img_arena_team_selected.png";//选中
static char IMG_ARENALIST_GLOD[] = "images/arena/arenaList/img_arenaList_gold.png";//冷却时间
static char IMG_ARENALIST_TIMES[] = "images/arena/arenaList/img_arenaList_times.png";//冷却次数
static char IMG_ARENALIST_RANKBG[] = "images/arena/arenaList/img_arenaList_rankbg.png";//排名背景
static char IMG_ARENALIST_HEADBG[] = "images/arena/img_arena_headbg.png";//头像背景
static char IMG_ARENALIST_HEADBOX[] = "images/arena/img_arena_headbox.png";//头像框
static char IMG_ARENALIST_RANK[] = "images/arena/img_arenaList_rank.png";//排名



//对战记录
static char IMG_ARENATEAM_FIGHTRECORED_DOWN[] = "images/arena/fightRecored/img_arena_fightRecored_down.png";//下降
static char IMG_ARENATEAM_FIGHTRECORED_UP[] = "images/arena/fightRecored/img_arena_fightRecored_up.png";//上涨
static char IMG_ARENATEAM_FIGHTRECORED_STAGE[] = "images/arena/fightRecored/img_arena_fightRecored_stage.png";//不变

static char IMG_ARENATEAM_FIGHTRECORED_LOSE[] = "images/arena/fightRecored/img_arena_fightRecored_lose.png";//失败
static char IMG_ARENATEAM_FIGHTRECORED_LOSEBG[] = "images/arena/fightRecored/img_arena_fightRecored_losebg.png";//失败背景
static char IMG_ARENATEAM_FIGHTRECORED_WIN[] = "images/arena/fightRecored/img_arena_fightRecored_win.png";//成功
static char IMG_ARENATEAM_FIGHTRECORED_WINBG[] = "images/arena/fightRecored/img_arena_fightRecored_winbg.png";//成功背景

static char IMG_DARK_DARKBG[] = "images/dark/image_dark_darkBg.png";//劫镖北京
static char IMG_DARK_FREETIMESWORD[] = "images/dark/image_dark_darkRobtimesWord.png";//免费强多数
static char IMG_DARK_DARKROBWORD[] = "images/dark/image_dark_darkRobWord.png";//抢夺


//新七日
static char IMG_SEVEENDAY_ONE[] = "images/activity/image_sevenday_one.png";//第一天
static char IMG_SEVEENDAY_TWO[] = "images/activity/image_sevenday_two.png";//第二天
static char IMG_SEVEENDAY_THREE[] = "images/activity/image_sevenday_three.png";//第三天
static char IMG_SEVEENDAY_FOUR[] = "images/activity/image_sevenday_four.png";//第四天
static char IMG_SEVEENDAY_FIVE[] = "images/activity/image_sevenday_five.png";//第五天
static char IMG_SEVEENDAY_SIX[] = "images/activity/image_sevenday_six.png";//第六天
static char IMG_SEVEENDAY_SEVEN[] = "images/activity/image_sevenday_seven.png";//第七天
static char IMG_SEVEENDAY_MODULEBG[] = "images/activity/image_sevenday_modulebg.png";//模块背景
static char IMG_SEVEENDAY_EVERYDAY[] = "images/activity/image_sevenday_everyday.png";//每日福利选中
static char IMG_SEVEENDAY_EVERYDAYUN[] = "images/activity/image_sevenday_everydayun.png";//每日福利没选中
static char IMG_SEVEENDAY_HALFBUY[] = "images/activity/image_sevenday_halfbuy.png";//半价抢购选中
static char IMG_SEVEENDAY_HALFBUYUN[] = "images/activity/image_sevenday_halfbuyun.png";//半价抢购没选中
static char IMG_SEVEENDAY_HAPPYWORD[] = "images/activity/image_sevenday_happyWord.png";//七天乐
static char IMG_SEVEENDAY_BG[] = "images/activity/image_sevenday_bg.png";//背景
static char IMG_SEVEENDAY_EVERYBOON[] = "images/activity/image_sevenday_everyboon.png";//每日福利
static char IMG_SEVEENDAY_HALFPRIVEBG[] = "images/activity/image_sevenday_halfpricebg.png";//半价抢购
static char IMG_SEVEENDAY_TITLE[] = "images/activity/image_sevenday_title%s.png";//选中title
static char IMG_SEVEENDAY_UNTITLE[] = "images/activity/image_sevenday_titleun%s.png";//未选中选中title
static char IMG_SEVEENDAY_CELLBG[] = "images/activity/image_sevenday_cellbg.png";//任务北京

/////创建角色、、、、、、、
static char IMG_CREATEROLE_DICE[] = "images/createRole/image_createRole_dice.png";//色子
static char IMG_CREATEROLE_NAMEBG[] = "images/createRole/image_createRole_nameBg.png";//名字背景
static char IMG_CREATEROLE_BG[] = "images/createRole/image_createRole_bg.png";//背景
static char IMG_CREATEROLE_TEXT[] = "images/createRole/image_createRole_text.png";//文字

#endif






