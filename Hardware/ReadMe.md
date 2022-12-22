# LED Strip Controller Hardware
# Summary
The hardware was developed using veroboard first to prove the concept and then a PCB was designed with extra features that include: reduced form factor, over current/voltage protection circuitry, better thermal and EMI management.
# Design
The design consists of two PCBs, one which is the LED controller and an optional Buttons Controller daughter board. The 3D Printed case utilises both however, if the user decided that they only wanted to use the device through USB then the board could be removed.

![Hardware Architecture](../docs/Diagrams-Hardware%20Architecture.png)

## LED Strip Controller

The LED Strip Controller hardware is responsible for controlling the LEDs along with maintaining the system. This hardware should be capable of driving a variety of different light strips and protecting the whole board from short circuits and over voltages. The 3D render of the PCB is shown below:

![LED Strip Controller]()

## Buttons Controller
As for the Buttons Controller board, this is a simple PCB board with buttons, that can be added to the main board through a simple ribbon cable. This is done so that optional buttons can be added to the system. The 3D render of the PCB is shown below:

![Buttons Controller]()

## 3D Printed Case Assembly

As for containing the hardware, a 3D printable case was designed and is shown below:
![3D printable Case]()

## Cable Wiring

# Improvements

# Useful Links
- [XT60 Connectors](https://www.aliexpress.com/item/1005004111518826.html?spm=a2g0o.order_list.0.0.44851802WtcK2c)
- [Terminal Crimps](https://www.aliexpress.com/item/1005004040825209.html?spm=a2g0o.productlist.0.0.7b09618cNrzGIX&algo_pvid=1400a7b4-9197-4d6a-b152-92a1a64300d6&algo_exp_id=1400a7b4-9197-4d6a-b152-92a1a64300d6-1&pdp_ext_f=%7B%22sku_id%22%3A%2212000028334234012%22%7D&pdp_npi=2%40dis%21GBP%216.94%215.2%21%21%21%21%21%402100bddb16647521768224542ea791%2112000028334234012%21sea&curPageLogUid=0NObb2zgCZaC)
- [Ferrel Crimps](https://www.aliexpress.com/item/1005004283026574.html?spm=a2g0o.detail.1000060.1.2b025a79uxZBof&gps-id=pcDetailBottomMoreThisSeller&scm=1007.13339.291025.0&scm_id=1007.13339.291025.0&scm-url=1007.13339.291025.0&pvid=82c1f2f2-f4eb-4113-b474-5a5eedb67d54&_t=gps-id:pcDetailBottomMoreThisSeller,scm-url:1007.13339.291025.0,pvid:82c1f2f2-f4eb-4113-b474-5a5eedb67d54,tpp_buckets:668%232846%238114%231999&pdp_ext_f=%7B%22sku_id%22%3A%2212000028621229126%22%2C%22sceneId%22%3A%223339%22%7D&pdp_npi=2%40dis%21GBP%218.57%215.57%21%21%21%21%21%40211b444016647521812691593e8c0a%2112000028621229126%21rec)
- [Switches](https://www.aliexpress.com/item/32743866390.html?spm=a2g0o.productlist.0.0.3cd4700cNdYXJ6&algo_pvid=e6b88297-a8ce-45f8-93eb-8b976bdea822&algo_exp_id=e6b88297-a8ce-45f8-93eb-8b976bdea822-3&pdp_ext_f=%7B%22sku_id%22%3A%2212000029574447281%22%7D&pdp_npi=2%40dis%21GBP%210.39%210.25%21%21%210.82%21%21%400b0a0ae216647521586066114e5989%2112000029574447281%21sea&curPageLogUid=3X8Abgou2M2X)
